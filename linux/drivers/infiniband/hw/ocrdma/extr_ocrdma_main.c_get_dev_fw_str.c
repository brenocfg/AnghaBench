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
struct TYPE_2__ {char* fw_ver; } ;
struct ocrdma_dev {TYPE_1__ attr; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_FW_VERSION_NAME_MAX ; 
 struct ocrdma_dev* get_ocrdma_dev (struct ib_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void get_dev_fw_str(struct ib_device *device, char *str)
{
	struct ocrdma_dev *dev = get_ocrdma_dev(device);

	snprintf(str, IB_FW_VERSION_NAME_MAX, "%s", &dev->attr.fw_ver[0]);
}