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
typedef  int /*<<< orphan*/  u8 ;
struct airspy {int /*<<< orphan*/  dev; TYPE_4__* lna_gain; TYPE_3__* lna_gain_auto; } ;
struct TYPE_6__ {int /*<<< orphan*/  val; } ;
struct TYPE_8__ {int val; TYPE_2__ cur; } ;
struct TYPE_5__ {int /*<<< orphan*/  val; } ;
struct TYPE_7__ {int val; TYPE_1__ cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SET_LNA_AGC ; 
 int /*<<< orphan*/  CMD_SET_LNA_GAIN ; 
 int airspy_ctrl_msg (struct airspy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int airspy_set_lna_gain(struct airspy *s)
{
	int ret;
	u8 u8tmp;

	dev_dbg(s->dev, "lna auto=%d->%d val=%d->%d\n",
			s->lna_gain_auto->cur.val, s->lna_gain_auto->val,
			s->lna_gain->cur.val, s->lna_gain->val);

	ret = airspy_ctrl_msg(s, CMD_SET_LNA_AGC, 0, s->lna_gain_auto->val,
			&u8tmp, 1);
	if (ret)
		goto err;

	if (s->lna_gain_auto->val == false) {
		ret = airspy_ctrl_msg(s, CMD_SET_LNA_GAIN, 0, s->lna_gain->val,
				&u8tmp, 1);
		if (ret)
			goto err;
	}
err:
	if (ret)
		dev_dbg(s->dev, "failed=%d\n", ret);

	return ret;
}