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
typedef  int /*<<< orphan*/  u8 ;
struct airspy {int /*<<< orphan*/  dev; TYPE_2__* if_gain; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; } ;
struct TYPE_4__ {int /*<<< orphan*/  val; TYPE_1__ cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SET_VGA_GAIN ; 
 int airspy_ctrl_msg (struct airspy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int airspy_set_if_gain(struct airspy *s)
{
	int ret;
	u8 u8tmp;

	dev_dbg(s->dev, "val=%d->%d\n", s->if_gain->cur.val, s->if_gain->val);

	ret = airspy_ctrl_msg(s, CMD_SET_VGA_GAIN, 0, s->if_gain->val,
			&u8tmp, 1);
	if (ret)
		dev_dbg(s->dev, "failed=%d\n", ret);

	return ret;
}