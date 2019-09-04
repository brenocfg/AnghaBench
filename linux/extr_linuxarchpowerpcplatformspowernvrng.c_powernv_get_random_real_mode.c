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
struct powernv_rng {int /*<<< orphan*/  regs_real; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_rm_readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powernv_rng ; 
 struct powernv_rng* raw_cpu_read (int /*<<< orphan*/ ) ; 
 unsigned long rng_whiten (struct powernv_rng*,int /*<<< orphan*/ ) ; 

int powernv_get_random_real_mode(unsigned long *v)
{
	struct powernv_rng *rng;

	rng = raw_cpu_read(powernv_rng);

	*v = rng_whiten(rng, __raw_rm_readq(rng->regs_real));

	return 1;
}