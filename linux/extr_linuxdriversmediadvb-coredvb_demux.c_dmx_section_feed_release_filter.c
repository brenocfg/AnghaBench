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
struct dvb_demux_filter {int /*<<< orphan*/  state; struct dvb_demux_filter* next; struct dvb_demux_feed* feed; } ;
struct dvb_demux_feed {struct dvb_demux_filter* filter; struct dvb_demux* demux; } ;
struct dvb_demux {int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; } ;
struct dmx_section_filter {int dummy; } ;
struct dmx_section_feed {int /*<<< orphan*/  (* stop_filtering ) (struct dmx_section_feed*) ;scalar_t__ is_filtering; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMX_STATE_FREE ; 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dmx_section_feed*) ; 

__attribute__((used)) static int dmx_section_feed_release_filter(struct dmx_section_feed *feed,
					   struct dmx_section_filter *filter)
{
	struct dvb_demux_filter *dvbdmxfilter = (struct dvb_demux_filter *)filter, *f;
	struct dvb_demux_feed *dvbdmxfeed = (struct dvb_demux_feed *)feed;
	struct dvb_demux *dvbdmx = dvbdmxfeed->demux;

	mutex_lock(&dvbdmx->mutex);

	if (dvbdmxfilter->feed != dvbdmxfeed) {
		mutex_unlock(&dvbdmx->mutex);
		return -EINVAL;
	}

	if (feed->is_filtering) {
		/* release dvbdmx->mutex as far as it is
		   acquired by stop_filtering() itself */
		mutex_unlock(&dvbdmx->mutex);
		feed->stop_filtering(feed);
		mutex_lock(&dvbdmx->mutex);
	}

	spin_lock_irq(&dvbdmx->lock);
	f = dvbdmxfeed->filter;

	if (f == dvbdmxfilter) {
		dvbdmxfeed->filter = dvbdmxfilter->next;
	} else {
		while (f->next != dvbdmxfilter)
			f = f->next;
		f->next = f->next->next;
	}

	dvbdmxfilter->state = DMX_STATE_FREE;
	spin_unlock_irq(&dvbdmx->lock);
	mutex_unlock(&dvbdmx->mutex);
	return 0;
}