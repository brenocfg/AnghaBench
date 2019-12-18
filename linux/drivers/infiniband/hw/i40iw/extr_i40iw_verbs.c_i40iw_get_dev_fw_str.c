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
typedef  int u32 ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int I40IW_FW_VERSION ; 
 int /*<<< orphan*/  IB_FW_VERSION_NAME_MAX ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void i40iw_get_dev_fw_str(struct ib_device *dev, char *str)
{
	u32 firmware_version = I40IW_FW_VERSION;

	snprintf(str, IB_FW_VERSION_NAME_MAX, "%u.%u", firmware_version,
		 (firmware_version & 0x000000ff));
}