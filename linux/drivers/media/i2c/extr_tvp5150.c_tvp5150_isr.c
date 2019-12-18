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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct tvp5150 {int lock; int /*<<< orphan*/  oe; TYPE_1__ sd; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TVP5150_INT_ACTIVE_REG_B ; 
 unsigned int TVP5150_INT_A_LOCK ; 
 unsigned int TVP5150_INT_A_LOCK_STATUS ; 
 int /*<<< orphan*/  TVP5150_INT_RESET_REG_B ; 
 int /*<<< orphan*/  TVP5150_INT_STATUS_REG_A ; 
 int /*<<< orphan*/  TVP5150_INT_STATUS_REG_B ; 
 int /*<<< orphan*/  TVP5150_MISC_CTL ; 
 unsigned int TVP5150_MISC_CTL_CLOCK_OE ; 
 unsigned int TVP5150_MISC_CTL_SYNC_OE ; 
 unsigned int TVP5150_MISC_CTL_YCBCR_OE ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  dev_dbg_lvl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  tvp5150_ev_fmt ; 
 int /*<<< orphan*/  v4l2_subdev_notify_event (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t tvp5150_isr(int irq, void *dev_id)
{
	struct tvp5150 *decoder = dev_id;
	struct regmap *map = decoder->regmap;
	unsigned int mask, active = 0, status = 0;

	mask = TVP5150_MISC_CTL_YCBCR_OE | TVP5150_MISC_CTL_SYNC_OE |
	       TVP5150_MISC_CTL_CLOCK_OE;

	regmap_read(map, TVP5150_INT_STATUS_REG_A, &status);
	if (status) {
		regmap_write(map, TVP5150_INT_STATUS_REG_A, status);

		if (status & TVP5150_INT_A_LOCK) {
			decoder->lock = !!(status & TVP5150_INT_A_LOCK_STATUS);
			dev_dbg_lvl(decoder->sd.dev, 1, debug,
				    "sync lo%s signal\n",
				    decoder->lock ? "ck" : "ss");
			v4l2_subdev_notify_event(&decoder->sd, &tvp5150_ev_fmt);
			regmap_update_bits(map, TVP5150_MISC_CTL, mask,
					   decoder->lock ? decoder->oe : 0);
		}

		return IRQ_HANDLED;
	}

	regmap_read(map, TVP5150_INT_ACTIVE_REG_B, &active);
	if (active) {
		status = 0;
		regmap_read(map, TVP5150_INT_STATUS_REG_B, &status);
		if (status)
			regmap_write(map, TVP5150_INT_RESET_REG_B, status);
	}

	return IRQ_HANDLED;
}