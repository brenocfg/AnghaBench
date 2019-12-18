#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union axis_conversion {int dummy; } axis_conversion ;
struct dmi_system_id {int /*<<< orphan*/  ident; scalar_t__ driver_data; } ;
struct TYPE_2__ {union axis_conversion ac; } ;

/* Variables and functions */
 TYPE_1__ lis3_dev ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lis3lv02d_dmi_matched(const struct dmi_system_id *dmi)
{
	lis3_dev.ac = *((union axis_conversion *)dmi->driver_data);
	pr_info("hardware type %s found\n", dmi->ident);

	return 1;
}