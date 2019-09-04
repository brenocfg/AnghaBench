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
struct hfi1_pportdata {int /*<<< orphan*/  port_type; int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_CONFIG_PORT_TABLE ; 
 int /*<<< orphan*/  PORT_TABLE_PORT_TYPE ; 
 int /*<<< orphan*/  PORT_TYPE_UNKNOWN ; 
 int get_platform_config_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void get_port_type(struct hfi1_pportdata *ppd)
{
	int ret;
	u32 temp;

	ret = get_platform_config_field(ppd->dd, PLATFORM_CONFIG_PORT_TABLE, 0,
					PORT_TABLE_PORT_TYPE, &temp,
					4);
	if (ret) {
		ppd->port_type = PORT_TYPE_UNKNOWN;
		return;
	}
	ppd->port_type = temp;
}