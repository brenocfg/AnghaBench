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
typedef  int /*<<< orphan*/  u64 ;
struct rc_dev {struct em28xx_IR* priv; } ;
struct em28xx_IR {struct em28xx* dev; } ;
struct em28xx {int chip_id; TYPE_1__* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CHIP_ID_EM28174 133 
#define  CHIP_ID_EM28178 132 
#define  CHIP_ID_EM2860 131 
#define  CHIP_ID_EM2874 130 
#define  CHIP_ID_EM2883 129 
#define  CHIP_ID_EM2884 128 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int em2860_ir_change_protocol (struct rc_dev*,int /*<<< orphan*/ *) ; 
 int em2874_ir_change_protocol (struct rc_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int em28xx_ir_change_protocol(struct rc_dev *rc_dev, u64 *rc_proto)
{
	struct em28xx_IR *ir = rc_dev->priv;
	struct em28xx *dev = ir->dev;

	/* Setup the proper handler based on the chip */
	switch (dev->chip_id) {
	case CHIP_ID_EM2860:
	case CHIP_ID_EM2883:
		return em2860_ir_change_protocol(rc_dev, rc_proto);
	case CHIP_ID_EM2884:
	case CHIP_ID_EM2874:
	case CHIP_ID_EM28174:
	case CHIP_ID_EM28178:
		return em2874_ir_change_protocol(rc_dev, rc_proto);
	default:
		dev_err(&ir->dev->intf->dev,
			"Unrecognized em28xx chip id 0x%02x: IR not supported\n",
			dev->chip_id);
		return -EINVAL;
	}
}