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
typedef  scalar_t__ u16 ;
struct kvaser_usb_dev_card_data_hydra {scalar_t__ transid; int /*<<< orphan*/  transid_lock; } ;
struct TYPE_2__ {struct kvaser_usb_dev_card_data_hydra hydra; } ;
struct kvaser_usb {TYPE_1__ card_data; } ;

/* Variables and functions */
 scalar_t__ KVASER_USB_HYDRA_MAX_TRANSID ; 
 scalar_t__ KVASER_USB_HYDRA_MIN_TRANSID ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u16 kvaser_usb_hydra_get_next_transid(struct kvaser_usb *dev)
{
	unsigned long flags;
	u16 transid;
	struct kvaser_usb_dev_card_data_hydra *card_data =
							&dev->card_data.hydra;

	spin_lock_irqsave(&card_data->transid_lock, flags);
	transid = card_data->transid;
	if (transid >= KVASER_USB_HYDRA_MAX_TRANSID)
		transid = KVASER_USB_HYDRA_MIN_TRANSID;
	else
		transid++;
	card_data->transid = transid;
	spin_unlock_irqrestore(&card_data->transid_lock, flags);

	return transid;
}