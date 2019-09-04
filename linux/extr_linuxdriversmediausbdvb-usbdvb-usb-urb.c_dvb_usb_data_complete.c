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
typedef  int /*<<< orphan*/  u8 ;
struct usb_data_stream {struct dvb_usb_adapter* user_priv; } ;
struct dvb_usb_adapter {scalar_t__ feedcount; int state; int /*<<< orphan*/  demux; } ;

/* Variables and functions */
 int DVB_USB_ADAP_STATE_DVB ; 
 int /*<<< orphan*/  dvb_dmx_swfilter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void dvb_usb_data_complete(struct usb_data_stream *stream, u8 *buffer, size_t length)
{
	struct dvb_usb_adapter *adap = stream->user_priv;
	if (adap->feedcount > 0 && adap->state & DVB_USB_ADAP_STATE_DVB)
		dvb_dmx_swfilter(&adap->demux, buffer, length);
}