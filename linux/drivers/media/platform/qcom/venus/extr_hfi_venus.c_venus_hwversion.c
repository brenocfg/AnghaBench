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
typedef  int u32 ;
struct venus_hfi_device {TYPE_1__* core; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRAPPER_HW_VERSION ; 
 int WRAPPER_HW_VERSION_MAJOR_VERSION_MASK ; 
 int WRAPPER_HW_VERSION_MAJOR_VERSION_SHIFT ; 
 int WRAPPER_HW_VERSION_MINOR_VERSION_MASK ; 
 int WRAPPER_HW_VERSION_MINOR_VERSION_SHIFT ; 
 int WRAPPER_HW_VERSION_STEP_VERSION_MASK ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int,int) ; 
 int venus_readl (struct venus_hfi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 venus_hwversion(struct venus_hfi_device *hdev)
{
	struct device *dev = hdev->core->dev;
	u32 ver = venus_readl(hdev, WRAPPER_HW_VERSION);
	u32 major, minor, step;

	major = ver & WRAPPER_HW_VERSION_MAJOR_VERSION_MASK;
	major = major >> WRAPPER_HW_VERSION_MAJOR_VERSION_SHIFT;
	minor = ver & WRAPPER_HW_VERSION_MINOR_VERSION_MASK;
	minor = minor >> WRAPPER_HW_VERSION_MINOR_VERSION_SHIFT;
	step = ver & WRAPPER_HW_VERSION_STEP_VERSION_MASK;

	dev_dbg(dev, "venus hw version %x.%x.%x\n", major, minor, step);

	return major;
}