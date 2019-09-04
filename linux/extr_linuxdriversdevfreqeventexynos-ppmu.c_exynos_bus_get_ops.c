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
struct of_device_id {scalar_t__ data; } ;
struct device_node {int dummy; } ;
struct devfreq_event_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  exynos_ppmu_id_match ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 

__attribute__((used)) static struct devfreq_event_ops *exynos_bus_get_ops(struct device_node *np)
{
	const struct of_device_id *match;

	match = of_match_node(exynos_ppmu_id_match, np);
	return (struct devfreq_event_ops *)match->data;
}