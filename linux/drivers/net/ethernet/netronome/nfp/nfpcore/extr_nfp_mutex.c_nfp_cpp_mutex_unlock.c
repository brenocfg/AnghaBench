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
typedef  int /*<<< orphan*/  u16 ;
struct nfp_cpp_mutex {int depth; scalar_t__ key; scalar_t__ address; struct nfp_cpp* cpp; int /*<<< orphan*/  target; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int EPERM ; 
 scalar_t__ NFP_CPP_ID (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_cpp_interface (struct nfp_cpp*) ; 
 int nfp_cpp_readl (struct nfp_cpp*,scalar_t__ const,scalar_t__,scalar_t__*) ; 
 int nfp_cpp_writel (struct nfp_cpp*,scalar_t__ const,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ nfp_mutex_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_mutex_unlocked (int /*<<< orphan*/ ) ; 

int nfp_cpp_mutex_unlock(struct nfp_cpp_mutex *mutex)
{
	const u32 muw = NFP_CPP_ID(mutex->target, 4, 0);    /* atomic_write */
	const u32 mur = NFP_CPP_ID(mutex->target, 3, 0);    /* atomic_read */
	struct nfp_cpp *cpp = mutex->cpp;
	u32 key, value;
	u16 interface;
	int err;

	interface = nfp_cpp_interface(cpp);

	if (mutex->depth > 1) {
		mutex->depth--;
		return 0;
	}

	err = nfp_cpp_readl(mutex->cpp, mur, mutex->address + 4, &key);
	if (err < 0)
		return err;

	if (key != mutex->key)
		return -EPERM;

	err = nfp_cpp_readl(mutex->cpp, mur, mutex->address, &value);
	if (err < 0)
		return err;

	if (value != nfp_mutex_locked(interface))
		return -EACCES;

	err = nfp_cpp_writel(cpp, muw, mutex->address,
			     nfp_mutex_unlocked(interface));
	if (err < 0)
		return err;

	mutex->depth = 0;
	return 0;
}