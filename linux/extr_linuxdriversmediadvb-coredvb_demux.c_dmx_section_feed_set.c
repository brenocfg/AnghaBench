#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_4__ {int check_crc; } ;
struct TYPE_3__ {TYPE_2__ sec; } ;
struct dvb_demux_feed {int pid; int /*<<< orphan*/  state; TYPE_1__ feed; struct dvb_demux* demux; } ;
struct dvb_demux {int /*<<< orphan*/  mutex; } ;
struct dmx_section_feed {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMX_STATE_READY ; 
 int EINVAL ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  dvb_demux_feed_add (struct dvb_demux_feed*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dmx_section_feed_set(struct dmx_section_feed *feed,
				u16 pid, int check_crc)
{
	struct dvb_demux_feed *dvbdmxfeed = (struct dvb_demux_feed *)feed;
	struct dvb_demux *dvbdmx = dvbdmxfeed->demux;

	if (pid > 0x1fff)
		return -EINVAL;

	if (mutex_lock_interruptible(&dvbdmx->mutex))
		return -ERESTARTSYS;

	dvb_demux_feed_add(dvbdmxfeed);

	dvbdmxfeed->pid = pid;
	dvbdmxfeed->feed.sec.check_crc = check_crc;

	dvbdmxfeed->state = DMX_STATE_READY;
	mutex_unlock(&dvbdmx->mutex);
	return 0;
}