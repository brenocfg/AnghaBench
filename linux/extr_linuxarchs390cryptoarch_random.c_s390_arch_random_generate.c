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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ ARCH_RNG_BUF_SIZE ; 
 scalar_t__ arch_rng_buf ; 
 scalar_t__ arch_rng_buf_idx ; 
 int /*<<< orphan*/  arch_rng_lock ; 
 int /*<<< orphan*/  atomic64_add (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  s390_arch_random_counter ; 
 int /*<<< orphan*/  spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

bool s390_arch_random_generate(u8 *buf, unsigned int nbytes)
{
	/* lock rng buffer */
	if (!spin_trylock(&arch_rng_lock))
		return false;

	/* try to resolve the requested amount of bytes from the buffer */
	arch_rng_buf_idx -= nbytes;
	if (arch_rng_buf_idx < ARCH_RNG_BUF_SIZE) {
		memcpy(buf, arch_rng_buf + arch_rng_buf_idx, nbytes);
		atomic64_add(nbytes, &s390_arch_random_counter);
		spin_unlock(&arch_rng_lock);
		return true;
	}

	/* not enough bytes in rng buffer, refill is done asynchronously */
	spin_unlock(&arch_rng_lock);

	return false;
}