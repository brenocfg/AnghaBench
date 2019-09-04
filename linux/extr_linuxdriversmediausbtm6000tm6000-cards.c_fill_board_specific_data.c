#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tm6000_core {size_t model; int /*<<< orphan*/  v4l2_dev; TYPE_1__* udev; int /*<<< orphan*/  quirks; int /*<<< orphan*/  rinput; int /*<<< orphan*/ * vinput; int /*<<< orphan*/  caps; int /*<<< orphan*/  demod_addr; int /*<<< orphan*/  ir_codes; int /*<<< orphan*/  gpio; int /*<<< orphan*/  tuner_addr; int /*<<< orphan*/  tuner_type; int /*<<< orphan*/  dev_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  rinput; int /*<<< orphan*/ * vinput; int /*<<< orphan*/  caps; int /*<<< orphan*/  demod_addr; int /*<<< orphan*/  ir_codes; int /*<<< orphan*/  gpio; int /*<<< orphan*/  tuner_addr; int /*<<< orphan*/  tuner_type; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TM6000_QUIRK_NO_USB_DELAY ; 
#define  TM6010_BOARD_HAUPPAUGE_900H 129 
#define  TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE 128 
 TYPE_2__* tm6000_boards ; 
 int tm6000_init (struct tm6000_core*) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fill_board_specific_data(struct tm6000_core *dev)
{
	int rc;

	dev->dev_type   = tm6000_boards[dev->model].type;
	dev->tuner_type = tm6000_boards[dev->model].tuner_type;
	dev->tuner_addr = tm6000_boards[dev->model].tuner_addr;

	dev->gpio = tm6000_boards[dev->model].gpio;

	dev->ir_codes = tm6000_boards[dev->model].ir_codes;

	dev->demod_addr = tm6000_boards[dev->model].demod_addr;

	dev->caps = tm6000_boards[dev->model].caps;

	dev->vinput[0] = tm6000_boards[dev->model].vinput[0];
	dev->vinput[1] = tm6000_boards[dev->model].vinput[1];
	dev->vinput[2] = tm6000_boards[dev->model].vinput[2];
	dev->rinput = tm6000_boards[dev->model].rinput;

	/* setup per-model quirks */
	switch (dev->model) {
	case TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE:
	case TM6010_BOARD_HAUPPAUGE_900H:
		dev->quirks |= TM6000_QUIRK_NO_USB_DELAY;
		break;

	default:
		break;
	}

	/* initialize hardware */
	rc = tm6000_init(dev);
	if (rc < 0)
		return rc;

	return v4l2_device_register(&dev->udev->dev, &dev->v4l2_dev);
}