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
struct flexcop_device {int dummy; } ;
struct dvb_demux_feed {TYPE_1__* demux; } ;
struct TYPE_2__ {struct flexcop_device* priv; } ;

/* Variables and functions */
 int flexcop_pid_feed_control (struct flexcop_device*,struct dvb_demux_feed*,int) ; 

__attribute__((used)) static int flexcop_dvb_start_feed(struct dvb_demux_feed *dvbdmxfeed)
{
	struct flexcop_device *fc = dvbdmxfeed->demux->priv;
	return flexcop_pid_feed_control(fc, dvbdmxfeed, 1);
}