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
struct coda_dev {size_t firmware; int /*<<< orphan*/  dev; TYPE_1__* devtype; } ;
struct TYPE_2__ {char** firmware; int /*<<< orphan*/  product; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  coda_fw_callback ; 
 int /*<<< orphan*/  coda_product_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct coda_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int coda_firmware_request(struct coda_dev *dev)
{
	char *fw;

	if (dev->firmware >= ARRAY_SIZE(dev->devtype->firmware))
		return -EINVAL;

	fw = dev->devtype->firmware[dev->firmware];

	dev_dbg(dev->dev, "requesting firmware '%s' for %s\n", fw,
		coda_product_name(dev->devtype->product));

	return request_firmware_nowait(THIS_MODULE, true, fw, dev->dev,
				       GFP_KERNEL, dev, coda_fw_callback);
}