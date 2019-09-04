#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct isar_hw {int /*<<< orphan*/ * open; int /*<<< orphan*/ * firmware; int /*<<< orphan*/ * release; int /*<<< orphan*/ * init; TYPE_2__* ch; void* hw; } ;
struct TYPE_4__ {int nr; int /*<<< orphan*/  ctrl; int /*<<< orphan*/ * send; } ;
struct TYPE_6__ {int nr; void* hw; TYPE_1__ ch; } ;
struct TYPE_5__ {struct isar_hw* is; TYPE_3__ bch; } ;

/* Variables and functions */
 int ISDN_P_B_HDLC ; 
 int ISDN_P_B_L2DTMF ; 
 int ISDN_P_B_MASK ; 
 int ISDN_P_B_MODEM_ASYNC ; 
 int ISDN_P_B_RAW ; 
 int ISDN_P_B_T30_FAX ; 
 int /*<<< orphan*/  MAX_DATA_MEM ; 
 int /*<<< orphan*/  free_isar ; 
 int /*<<< orphan*/  init_isar ; 
 int /*<<< orphan*/  isar_bctrl ; 
 int /*<<< orphan*/  isar_l2l1 ; 
 int /*<<< orphan*/  isar_open ; 
 int /*<<< orphan*/  load_firmware ; 
 int /*<<< orphan*/  mISDN_initbchannel (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

u32
mISDNisar_init(struct isar_hw *isar, void *hw)
{
	u32 ret, i;

	isar->hw = hw;
	for (i = 0; i < 2; i++) {
		isar->ch[i].bch.nr = i + 1;
		mISDN_initbchannel(&isar->ch[i].bch, MAX_DATA_MEM, 32);
		isar->ch[i].bch.ch.nr = i + 1;
		isar->ch[i].bch.ch.send = &isar_l2l1;
		isar->ch[i].bch.ch.ctrl = isar_bctrl;
		isar->ch[i].bch.hw = hw;
		isar->ch[i].is = isar;
	}

	isar->init = &init_isar;
	isar->release = &free_isar;
	isar->firmware = &load_firmware;
	isar->open = &isar_open;

	ret =	(1 << (ISDN_P_B_RAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDLC & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_L2DTMF & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_MODEM_ASYNC & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_T30_FAX & ISDN_P_B_MASK));

	return ret;
}