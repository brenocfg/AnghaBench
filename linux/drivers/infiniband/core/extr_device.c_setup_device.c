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
struct ib_udata {int /*<<< orphan*/  inlen; int /*<<< orphan*/  outlen; } ;
struct TYPE_2__ {int (* query_device ) (struct ib_device*,int /*<<< orphan*/ *,struct ib_udata*) ;} ;
struct ib_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  attrs; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ib_device_check_mandatory (struct ib_device*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup_dma_device (struct ib_device*) ; 
 int setup_port_data (struct ib_device*) ; 
 int stub1 (struct ib_device*,int /*<<< orphan*/ *,struct ib_udata*) ; 

__attribute__((used)) static int setup_device(struct ib_device *device)
{
	struct ib_udata uhw = {.outlen = 0, .inlen = 0};
	int ret;

	setup_dma_device(device);
	ib_device_check_mandatory(device);

	ret = setup_port_data(device);
	if (ret) {
		dev_warn(&device->dev, "Couldn't create per-port data\n");
		return ret;
	}

	memset(&device->attrs, 0, sizeof(device->attrs));
	ret = device->ops.query_device(device, &device->attrs, &uhw);
	if (ret) {
		dev_warn(&device->dev,
			 "Couldn't query the device attributes\n");
		return ret;
	}

	return 0;
}