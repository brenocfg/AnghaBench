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
typedef  int /*<<< orphan*/  u32 ;
struct lpddr2_timings {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline const struct lpddr2_timings
	*of_get_ddr_timings(struct device_node *np_ddr, struct device *dev,
	u32 device_type, u32 *nr_frequencies)
{
	return NULL;
}