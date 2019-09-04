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
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPU_CS_SCIACMDARG0 ; 
 int CPU_CS_SCIACMDARG0_ERROR_STATUS_MASK ; 
 int /*<<< orphan*/  CPU_CS_SCIACMDARG3 ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  VIDC_CTRL_INIT ; 
 int /*<<< orphan*/  VIDC_CTRL_INIT_CTRL_SHIFT ; 
 int /*<<< orphan*/  WRAPPER_INTR_MASK ; 
 int WRAPPER_INTR_MASK_A2HVCODEC_MASK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int venus_readl (struct venus_hfi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venus_writel (struct venus_hfi_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int venus_boot_core(struct venus_hfi_device *hdev)
{
	struct device *dev = hdev->core->dev;
	static const unsigned int max_tries = 100;
	u32 ctrl_status = 0;
	unsigned int count = 0;
	int ret = 0;

	venus_writel(hdev, VIDC_CTRL_INIT, BIT(VIDC_CTRL_INIT_CTRL_SHIFT));
	venus_writel(hdev, WRAPPER_INTR_MASK, WRAPPER_INTR_MASK_A2HVCODEC_MASK);
	venus_writel(hdev, CPU_CS_SCIACMDARG3, 1);

	while (!ctrl_status && count < max_tries) {
		ctrl_status = venus_readl(hdev, CPU_CS_SCIACMDARG0);
		if ((ctrl_status & CPU_CS_SCIACMDARG0_ERROR_STATUS_MASK) == 4) {
			dev_err(dev, "invalid setting for UC_REGION\n");
			ret = -EINVAL;
			break;
		}

		usleep_range(500, 1000);
		count++;
	}

	if (count >= max_tries)
		ret = -ETIMEDOUT;

	return ret;
}