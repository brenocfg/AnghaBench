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
struct dvb_demux_feed {int /*<<< orphan*/  type; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  deb_ts (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dvb_usb_ctrl_feed (struct dvb_demux_feed*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dvb_usb_stop_feed(struct dvb_demux_feed *dvbdmxfeed)
{
	deb_ts("stop pid: 0x%04x, feedtype: %d\n", dvbdmxfeed->pid, dvbdmxfeed->type);
	return dvb_usb_ctrl_feed(dvbdmxfeed, 0);
}