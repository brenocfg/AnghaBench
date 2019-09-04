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
struct TYPE_5__ {scalar_t__ txerr; scalar_t__ rxerr; } ;
struct kvaser_usb_net_priv {TYPE_2__ bec; } ;
struct TYPE_6__ {int other_ch_status; int /*<<< orphan*/  error_state; } ;
struct kvaser_usb_err_summary {unsigned int channel; scalar_t__ txerr; scalar_t__ rxerr; int status; TYPE_3__ usbcan; } ;
struct kvaser_usb {unsigned int nchannels; struct kvaser_usb_net_priv** nets; TYPE_1__* intf; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int M16C_STATE_BUS_ERROR ; 
 int /*<<< orphan*/  USBCAN_ERROR_STATE_BUSERROR ; 
 int /*<<< orphan*/  USBCAN_ERROR_STATE_RX_ERROR ; 
 int /*<<< orphan*/  USBCAN_ERROR_STATE_TX_ERROR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  kvaser_usb_leaf_rx_error (struct kvaser_usb const*,struct kvaser_usb_err_summary*) ; 

__attribute__((used)) static void
kvaser_usb_leaf_usbcan_conditionally_rx_error(const struct kvaser_usb *dev,
					      struct kvaser_usb_err_summary *es)
{
	struct kvaser_usb_net_priv *priv;
	unsigned int channel;
	bool report_error;

	channel = es->channel;
	if (channel >= dev->nchannels) {
		dev_err(&dev->intf->dev,
			"Invalid channel number (%d)\n", channel);
		return;
	}

	priv = dev->nets[channel];
	report_error = false;

	if (es->txerr != priv->bec.txerr) {
		es->usbcan.error_state |= USBCAN_ERROR_STATE_TX_ERROR;
		report_error = true;
	}
	if (es->rxerr != priv->bec.rxerr) {
		es->usbcan.error_state |= USBCAN_ERROR_STATE_RX_ERROR;
		report_error = true;
	}
	if ((es->status & M16C_STATE_BUS_ERROR) &&
	    !(es->usbcan.other_ch_status & M16C_STATE_BUS_ERROR)) {
		es->usbcan.error_state |= USBCAN_ERROR_STATE_BUSERROR;
		report_error = true;
	}

	if (report_error)
		kvaser_usb_leaf_rx_error(dev, es);
}