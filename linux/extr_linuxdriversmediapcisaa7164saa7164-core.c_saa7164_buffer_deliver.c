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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  demux; } ;
struct saa7164_port {TYPE_1__ dvb; } ;
struct saa7164_buffer {scalar_t__ cpu; struct saa7164_port* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7164_TS_NUMBER_OF_LINES ; 
 int /*<<< orphan*/  dvb_dmx_swfilter_packets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void saa7164_buffer_deliver(struct saa7164_buffer *buf)
{
	struct saa7164_port *port = buf->port;

	/* Feed the transport payload into the kernel demux */
	dvb_dmx_swfilter_packets(&port->dvb.demux, (u8 *)buf->cpu,
		SAA7164_TS_NUMBER_OF_LINES);

}