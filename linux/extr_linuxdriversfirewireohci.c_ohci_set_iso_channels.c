#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
struct fw_ohci {int ir_context_channels; int mc_channels; int /*<<< orphan*/  lock; } ;
struct fw_iso_context {int type; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  FW_ISO_CONTEXT_RECEIVE_MULTICHANNEL 128 
 struct fw_ohci* fw_ohci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_multichannel_mask (struct fw_ohci*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ohci_set_iso_channels(struct fw_iso_context *base, u64 *channels)
{
	struct fw_ohci *ohci = fw_ohci(base->card);
	unsigned long flags;
	int ret;

	switch (base->type) {
	case FW_ISO_CONTEXT_RECEIVE_MULTICHANNEL:

		spin_lock_irqsave(&ohci->lock, flags);

		/* Don't allow multichannel to grab other contexts' channels. */
		if (~ohci->ir_context_channels & ~ohci->mc_channels & *channels) {
			*channels = ohci->ir_context_channels;
			ret = -EBUSY;
		} else {
			set_multichannel_mask(ohci, *channels);
			ret = 0;
		}

		spin_unlock_irqrestore(&ohci->lock, flags);

		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}