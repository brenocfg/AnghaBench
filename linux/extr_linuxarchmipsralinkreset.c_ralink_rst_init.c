#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  reset_controller_register (TYPE_1__*) ; 
 TYPE_1__ reset_dev ; 

void ralink_rst_init(void)
{
	reset_dev.of_node = of_find_compatible_node(NULL, NULL,
						"ralink,rt2880-reset");
	if (!reset_dev.of_node)
		pr_err("Failed to find reset controller node");
	else
		reset_controller_register(&reset_dev);
}