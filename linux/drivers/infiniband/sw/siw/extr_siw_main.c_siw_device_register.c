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
struct ib_device {int dummy; } ;
struct siw_device {TYPE_1__* netdev; int /*<<< orphan*/  vendor_part_id; struct ib_device base_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ib_register_device (struct ib_device*,char const*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  siw_dbg (struct ib_device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int siw_device_register(struct siw_device *sdev, const char *name)
{
	struct ib_device *base_dev = &sdev->base_dev;
	static int dev_id = 1;
	int rv;

	rv = ib_register_device(base_dev, name);
	if (rv) {
		pr_warn("siw: device registration error %d\n", rv);
		return rv;
	}
	sdev->vendor_part_id = dev_id++;

	siw_dbg(base_dev, "HWaddr=%pM\n", sdev->netdev->dev_addr);

	return 0;
}