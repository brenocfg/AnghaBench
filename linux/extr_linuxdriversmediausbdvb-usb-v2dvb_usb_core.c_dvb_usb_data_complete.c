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
struct dvb_usb_adapter {int /*<<< orphan*/  demux; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_dmx_swfilter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void dvb_usb_data_complete(struct usb_data_stream *stream, u8 *buf,
		size_t len)
{
	struct dvb_usb_adapter *adap = stream->user_priv;
	dvb_dmx_swfilter(&adap->demux, buf, len);
}