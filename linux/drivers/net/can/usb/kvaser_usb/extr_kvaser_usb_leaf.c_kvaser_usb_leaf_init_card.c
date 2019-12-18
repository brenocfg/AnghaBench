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
struct kvaser_usb_dev_card_data {int /*<<< orphan*/  ctrlmode_supported; } ;
struct kvaser_usb {int /*<<< orphan*/ * cfg; struct kvaser_usb_dev_card_data card_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_CTRLMODE_3_SAMPLES ; 
 int /*<<< orphan*/  kvaser_usb_leaf_dev_cfg ; 

__attribute__((used)) static int kvaser_usb_leaf_init_card(struct kvaser_usb *dev)
{
	struct kvaser_usb_dev_card_data *card_data = &dev->card_data;

	dev->cfg = &kvaser_usb_leaf_dev_cfg;
	card_data->ctrlmode_supported |= CAN_CTRLMODE_3_SAMPLES;

	return 0;
}