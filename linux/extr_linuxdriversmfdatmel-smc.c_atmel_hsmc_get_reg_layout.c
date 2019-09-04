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
struct of_device_id {struct atmel_hsmc_reg_layout const* data; } ;
struct device_node {int dummy; } ;
struct atmel_hsmc_reg_layout {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct atmel_hsmc_reg_layout const* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_smc_ids ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 

const struct atmel_hsmc_reg_layout *
atmel_hsmc_get_reg_layout(struct device_node *np)
{
	const struct of_device_id *match;

	match = of_match_node(atmel_smc_ids, np);

	return match ? match->data : ERR_PTR(-EINVAL);
}