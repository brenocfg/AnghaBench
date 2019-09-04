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
struct lpddr2_timings {int /*<<< orphan*/  tDQSCK_max_derated; int /*<<< orphan*/  tRAS_max_ns; int /*<<< orphan*/  tZQinit; int /*<<< orphan*/  tZQCL; int /*<<< orphan*/  tZQCS; int /*<<< orphan*/  tFAW; int /*<<< orphan*/  tDQSCK_max; int /*<<< orphan*/  tCKESR; int /*<<< orphan*/  tRTP; int /*<<< orphan*/  tXP; int /*<<< orphan*/  tWTR; int /*<<< orphan*/  tRRD; int /*<<< orphan*/  tRAS_min; int /*<<< orphan*/  tWR; int /*<<< orphan*/  tRCD; int /*<<< orphan*/  tRPab; int /*<<< orphan*/  min_freq; int /*<<< orphan*/  max_freq; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int of_do_get_timings(struct device_node *np,
		struct lpddr2_timings *tim)
{
	int ret;

	ret = of_property_read_u32(np, "max-freq", &tim->max_freq);
	ret |= of_property_read_u32(np, "min-freq", &tim->min_freq);
	ret |= of_property_read_u32(np, "tRPab", &tim->tRPab);
	ret |= of_property_read_u32(np, "tRCD", &tim->tRCD);
	ret |= of_property_read_u32(np, "tWR", &tim->tWR);
	ret |= of_property_read_u32(np, "tRAS-min", &tim->tRAS_min);
	ret |= of_property_read_u32(np, "tRRD", &tim->tRRD);
	ret |= of_property_read_u32(np, "tWTR", &tim->tWTR);
	ret |= of_property_read_u32(np, "tXP", &tim->tXP);
	ret |= of_property_read_u32(np, "tRTP", &tim->tRTP);
	ret |= of_property_read_u32(np, "tCKESR", &tim->tCKESR);
	ret |= of_property_read_u32(np, "tDQSCK-max", &tim->tDQSCK_max);
	ret |= of_property_read_u32(np, "tFAW", &tim->tFAW);
	ret |= of_property_read_u32(np, "tZQCS", &tim->tZQCS);
	ret |= of_property_read_u32(np, "tZQCL", &tim->tZQCL);
	ret |= of_property_read_u32(np, "tZQinit", &tim->tZQinit);
	ret |= of_property_read_u32(np, "tRAS-max-ns", &tim->tRAS_max_ns);
	ret |= of_property_read_u32(np, "tDQSCK-max-derated",
		&tim->tDQSCK_max_derated);

	return ret;
}