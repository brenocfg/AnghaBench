#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nfp_cpp_mutex {int depth; scalar_t__ key; scalar_t__ address; struct nfp_cpp* cpp; int /*<<< orphan*/  target; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int E2BIG ; 
 int EBUSY ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ NFP_CPP_ID (int /*<<< orphan*/ ,int,int) ; 
 int NFP_MUTEX_DEPTH_MAX ; 
 int /*<<< orphan*/  nfp_cpp_interface (struct nfp_cpp*) ; 
 int nfp_cpp_readl (struct nfp_cpp*,scalar_t__ const,scalar_t__,scalar_t__*) ; 
 int nfp_cpp_writel (struct nfp_cpp*,scalar_t__ const,scalar_t__,scalar_t__) ; 
 scalar_t__ nfp_mutex_is_locked (scalar_t__) ; 
 scalar_t__ nfp_mutex_is_unlocked (scalar_t__) ; 
 scalar_t__ nfp_mutex_locked (int /*<<< orphan*/ ) ; 

int nfp_cpp_mutex_trylock(struct nfp_cpp_mutex *mutex)
{
	const u32 muw = NFP_CPP_ID(mutex->target, 4, 0);    /* atomic_write */
	const u32 mus = NFP_CPP_ID(mutex->target, 5, 3);    /* test_set_imm */
	const u32 mur = NFP_CPP_ID(mutex->target, 3, 0);    /* atomic_read */
	struct nfp_cpp *cpp = mutex->cpp;
	u32 key, value, tmp;
	int err;

	if (mutex->depth > 0) {
		if (mutex->depth == NFP_MUTEX_DEPTH_MAX)
			return -E2BIG;
		mutex->depth++;
		return 0;
	}

	/* Verify that the lock marker is not damaged */
	err = nfp_cpp_readl(cpp, mur, mutex->address + 4, &key);
	if (err < 0)
		return err;

	if (key != mutex->key)
		return -EPERM;

	/* Compare against the unlocked state, and if true,
	 * write the interface id into the top 16 bits, and
	 * mark as locked.
	 */
	value = nfp_mutex_locked(nfp_cpp_interface(cpp));

	/* We use test_set_imm here, as it implies a read
	 * of the current state, and sets the bits in the
	 * bytemask of the command to 1s. Since the mutex
	 * is guaranteed to be 64-bit aligned, the bytemask
	 * of this 32-bit command is ensured to be 8'b00001111,
	 * which implies that the lower 4 bits will be set to
	 * ones regardless of the initial state.
	 *
	 * Since this is a 'Readback' operation, with no Pull
	 * data, we can treat this as a normal Push (read)
	 * atomic, which returns the original value.
	 */
	err = nfp_cpp_readl(cpp, mus, mutex->address, &tmp);
	if (err < 0)
		return err;

	/* Was it unlocked? */
	if (nfp_mutex_is_unlocked(tmp)) {
		/* The read value can only be 0x....0000 in the unlocked state.
		 * If there was another contending for this lock, then
		 * the lock state would be 0x....000f
		 */

		/* Write our owner ID into the lock
		 * While not strictly necessary, this helps with
		 * debug and bookkeeping.
		 */
		err = nfp_cpp_writel(cpp, muw, mutex->address, value);
		if (err < 0)
			return err;

		mutex->depth = 1;
		return 0;
	}

	return nfp_mutex_is_locked(tmp) ? -EBUSY : -EINVAL;
}