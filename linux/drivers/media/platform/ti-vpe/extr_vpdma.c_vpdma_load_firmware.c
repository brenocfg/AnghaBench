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
struct vpdma_data {TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ VPDMA_FIRMWARE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,scalar_t__) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,char const*,struct device*,int /*<<< orphan*/ ,struct vpdma_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpdma_firmware_cb ; 

__attribute__((used)) static int vpdma_load_firmware(struct vpdma_data *vpdma)
{
	int r;
	struct device *dev = &vpdma->pdev->dev;

	r = request_firmware_nowait(THIS_MODULE, 1,
		(const char *) VPDMA_FIRMWARE, dev, GFP_KERNEL, vpdma,
		vpdma_firmware_cb);
	if (r) {
		dev_err(dev, "firmware not available %s\n", VPDMA_FIRMWARE);
		return r;
	} else {
		dev_info(dev, "loading firmware %s\n", VPDMA_FIRMWARE);
	}

	return 0;
}