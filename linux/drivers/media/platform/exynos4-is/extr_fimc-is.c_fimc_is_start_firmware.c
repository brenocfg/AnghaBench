#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* f_w; } ;
struct TYPE_5__ {int /*<<< orphan*/  vaddr; } ;
struct fimc_is {TYPE_4__ fw; TYPE_1__ memory; TYPE_2__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FIMC_IS_FW_LOAD_TIMEOUT ; 
 int /*<<< orphan*/  IS_ST_A5_PWR_ON ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int fimc_is_cpu_set_power (struct fimc_is*,int) ; 
 int fimc_is_wait_event (struct fimc_is*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

int fimc_is_start_firmware(struct fimc_is *is)
{
	struct device *dev = &is->pdev->dev;
	int ret;

	if (is->fw.f_w == NULL) {
		dev_err(dev, "firmware is not loaded\n");
		return -EINVAL;
	}

	memcpy(is->memory.vaddr, is->fw.f_w->data, is->fw.f_w->size);
	wmb();

	ret = fimc_is_cpu_set_power(is, 1);
	if (ret < 0)
		return ret;

	ret = fimc_is_wait_event(is, IS_ST_A5_PWR_ON, 1,
				 msecs_to_jiffies(FIMC_IS_FW_LOAD_TIMEOUT));
	if (ret < 0)
		dev_err(dev, "FIMC-IS CPU power on failed\n");

	return ret;
}