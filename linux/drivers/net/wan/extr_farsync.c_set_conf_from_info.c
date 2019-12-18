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
struct fstioc_info {int valid; scalar_t__ proto; int invertClock; unsigned char lineSpeed; int clockSource; scalar_t__ framing; int structure; int interface; int coding; int lineBuildOut; int equalizer; int transparentMode; int loopMode; int range; int txBufferMode; int rxBufferMode; int startingSlot; int losThreshold; char idleCode; int /*<<< orphan*/  debug; int /*<<< orphan*/  cardMode; } ;
struct fst_port_info {size_t index; scalar_t__ mode; } ;
struct fst_card_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  invertClock; } ;
struct TYPE_3__ {int /*<<< orphan*/  idleCode; int /*<<< orphan*/  enableIdleCode; int /*<<< orphan*/  losThreshold; int /*<<< orphan*/  startingSlot; int /*<<< orphan*/  rxBufferMode; int /*<<< orphan*/  txBufferMode; int /*<<< orphan*/  range; int /*<<< orphan*/  loopMode; int /*<<< orphan*/  transparentMode; int /*<<< orphan*/  equalizer; int /*<<< orphan*/  lineBuildOut; int /*<<< orphan*/  coding; int /*<<< orphan*/  interface; int /*<<< orphan*/  structure; int /*<<< orphan*/  framing; int /*<<< orphan*/  clocking; int /*<<< orphan*/  dataRate; } ;

/* Variables and functions */
 scalar_t__ E1 ; 
 int EINVAL ; 
 unsigned char FRAMING_E1 ; 
 unsigned char FRAMING_J1 ; 
 unsigned char FRAMING_T1 ; 
 int FSTVAL_CABLE ; 
 int FSTVAL_DEBUG ; 
 int FSTVAL_MODE ; 
 int FSTVAL_PHASE ; 
 int FSTVAL_PROTO ; 
 int FSTVAL_SPEED ; 
 int FSTVAL_TE1 ; 
 scalar_t__ FST_GEN_HDLC ; 
 scalar_t__ FST_RAW ; 
 int /*<<< orphan*/  FST_WRB (struct fst_card_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FST_WRL (struct fst_card_info*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  FST_WRW (struct fst_card_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ J1 ; 
 scalar_t__ T1 ; 
 int /*<<< orphan*/  cardMode ; 
 int /*<<< orphan*/  fst_debug_mask ; 
 TYPE_2__* portConfig ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 TYPE_1__ suConfig ; 

__attribute__((used)) static int
set_conf_from_info(struct fst_card_info *card, struct fst_port_info *port,
		   struct fstioc_info *info)
{
	int err;
	unsigned char my_framing;

	/* Set things according to the user set valid flags 
	 * Several of the old options have been invalidated/replaced by the 
	 * generic hdlc package.
	 */
	err = 0;
	if (info->valid & FSTVAL_PROTO) {
		if (info->proto == FST_RAW)
			port->mode = FST_RAW;
		else
			port->mode = FST_GEN_HDLC;
	}

	if (info->valid & FSTVAL_CABLE)
		err = -EINVAL;

	if (info->valid & FSTVAL_SPEED)
		err = -EINVAL;

	if (info->valid & FSTVAL_PHASE)
		FST_WRB(card, portConfig[port->index].invertClock,
			info->invertClock);
	if (info->valid & FSTVAL_MODE)
		FST_WRW(card, cardMode, info->cardMode);
	if (info->valid & FSTVAL_TE1) {
		FST_WRL(card, suConfig.dataRate, info->lineSpeed);
		FST_WRB(card, suConfig.clocking, info->clockSource);
		my_framing = FRAMING_E1;
		if (info->framing == E1)
			my_framing = FRAMING_E1;
		if (info->framing == T1)
			my_framing = FRAMING_T1;
		if (info->framing == J1)
			my_framing = FRAMING_J1;
		FST_WRB(card, suConfig.framing, my_framing);
		FST_WRB(card, suConfig.structure, info->structure);
		FST_WRB(card, suConfig.interface, info->interface);
		FST_WRB(card, suConfig.coding, info->coding);
		FST_WRB(card, suConfig.lineBuildOut, info->lineBuildOut);
		FST_WRB(card, suConfig.equalizer, info->equalizer);
		FST_WRB(card, suConfig.transparentMode, info->transparentMode);
		FST_WRB(card, suConfig.loopMode, info->loopMode);
		FST_WRB(card, suConfig.range, info->range);
		FST_WRB(card, suConfig.txBufferMode, info->txBufferMode);
		FST_WRB(card, suConfig.rxBufferMode, info->rxBufferMode);
		FST_WRB(card, suConfig.startingSlot, info->startingSlot);
		FST_WRB(card, suConfig.losThreshold, info->losThreshold);
		if (info->idleCode)
			FST_WRB(card, suConfig.enableIdleCode, 1);
		else
			FST_WRB(card, suConfig.enableIdleCode, 0);
		FST_WRB(card, suConfig.idleCode, info->idleCode);
#if FST_DEBUG
		if (info->valid & FSTVAL_TE1) {
			printk("Setting TE1 data\n");
			printk("Line Speed = %d\n", info->lineSpeed);
			printk("Start slot = %d\n", info->startingSlot);
			printk("Clock source = %d\n", info->clockSource);
			printk("Framing = %d\n", my_framing);
			printk("Structure = %d\n", info->structure);
			printk("interface = %d\n", info->interface);
			printk("Coding = %d\n", info->coding);
			printk("Line build out = %d\n", info->lineBuildOut);
			printk("Equaliser = %d\n", info->equalizer);
			printk("Transparent mode = %d\n",
			       info->transparentMode);
			printk("Loop mode = %d\n", info->loopMode);
			printk("Range = %d\n", info->range);
			printk("Tx Buffer mode = %d\n", info->txBufferMode);
			printk("Rx Buffer mode = %d\n", info->rxBufferMode);
			printk("LOS Threshold = %d\n", info->losThreshold);
			printk("Idle Code = %d\n", info->idleCode);
		}
#endif
	}
#if FST_DEBUG
	if (info->valid & FSTVAL_DEBUG) {
		fst_debug_mask = info->debug;
	}
#endif

	return err;
}