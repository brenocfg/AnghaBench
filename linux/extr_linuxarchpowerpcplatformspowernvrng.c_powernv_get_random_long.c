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
struct powernv_rng {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 struct powernv_rng* get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powernv_rng ; 
 int /*<<< orphan*/  put_cpu_var (struct powernv_rng*) ; 
 unsigned long rng_whiten (struct powernv_rng*,int /*<<< orphan*/ ) ; 

int powernv_get_random_long(unsigned long *v)
{
	struct powernv_rng *rng;

	rng = get_cpu_var(powernv_rng);

	*v = rng_whiten(rng, in_be64(rng->regs));

	put_cpu_var(rng);

	return 1;
}