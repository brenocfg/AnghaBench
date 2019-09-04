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
struct sii8620 {int error; struct rc_dev* rc_dev; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bustype; } ;
struct rc_dev {char* input_phys; char* driver_name; char* device_name; int /*<<< orphan*/  allowed_protocols; int /*<<< orphan*/  map_name; TYPE_1__ input_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_VIRTUAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  RC_DRIVER_SCANCODE ; 
 int /*<<< orphan*/  RC_MAP_CEC ; 
 int /*<<< orphan*/  RC_PROTO_BIT_CEC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct rc_dev* rc_allocate_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 

__attribute__((used)) static void sii8620_init_rcp_input_dev(struct sii8620 *ctx)
{
	struct rc_dev *rc_dev;
	int ret;

	rc_dev = rc_allocate_device(RC_DRIVER_SCANCODE);
	if (!rc_dev) {
		dev_err(ctx->dev, "Failed to allocate RC device\n");
		ctx->error = -ENOMEM;
		return;
	}

	rc_dev->input_phys = "sii8620/input0";
	rc_dev->input_id.bustype = BUS_VIRTUAL;
	rc_dev->map_name = RC_MAP_CEC;
	rc_dev->allowed_protocols = RC_PROTO_BIT_CEC;
	rc_dev->driver_name = "sii8620";
	rc_dev->device_name = "sii8620";

	ret = rc_register_device(rc_dev);

	if (ret) {
		dev_err(ctx->dev, "Failed to register RC device\n");
		ctx->error = ret;
		rc_free_device(ctx->rc_dev);
		return;
	}
	ctx->rc_dev = rc_dev;
}