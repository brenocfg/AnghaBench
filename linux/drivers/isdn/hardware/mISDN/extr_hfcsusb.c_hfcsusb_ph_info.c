#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ph_info_dch {int dummy; } ;
struct ph_info_ch {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  Flags; int /*<<< orphan*/  protocol; } ;
struct TYPE_8__ {int num_bch; int /*<<< orphan*/  state; TYPE_1__ ch; } ;
struct ph_info {TYPE_4__* bch; TYPE_2__ dch; } ;
struct TYPE_12__ {int nrbchan; int /*<<< orphan*/  D; } ;
struct dchannel {TYPE_6__ dev; int /*<<< orphan*/  state; int /*<<< orphan*/  Flags; } ;
struct hfcsusb {TYPE_5__* bch; int /*<<< orphan*/  protocol; struct dchannel dch; } ;
struct TYPE_9__ {int /*<<< orphan*/  protocol; } ;
struct TYPE_11__ {int /*<<< orphan*/  Flags; TYPE_3__ ch; } ;
struct TYPE_10__ {int /*<<< orphan*/  Flags; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MISDN_ID_ANY ; 
 int /*<<< orphan*/  MPH_INFORMATION_IND ; 
 int /*<<< orphan*/  _queue_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ph_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch ; 
 int /*<<< orphan*/  kfree (struct ph_info*) ; 
 struct ph_info* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_size (struct ph_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
hfcsusb_ph_info(struct hfcsusb *hw)
{
	struct ph_info *phi;
	struct dchannel *dch = &hw->dch;
	int i;

	phi = kzalloc(struct_size(phi, bch, dch->dev.nrbchan), GFP_ATOMIC);
	if (!phi)
		return;

	phi->dch.ch.protocol = hw->protocol;
	phi->dch.ch.Flags = dch->Flags;
	phi->dch.state = dch->state;
	phi->dch.num_bch = dch->dev.nrbchan;
	for (i = 0; i < dch->dev.nrbchan; i++) {
		phi->bch[i].protocol = hw->bch[i].ch.protocol;
		phi->bch[i].Flags = hw->bch[i].Flags;
	}
	_queue_data(&dch->dev.D, MPH_INFORMATION_IND, MISDN_ID_ANY,
		    sizeof(struct ph_info_dch) + dch->dev.nrbchan *
		    sizeof(struct ph_info_ch), phi, GFP_ATOMIC);
	kfree(phi);
}