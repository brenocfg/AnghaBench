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
struct TYPE_5__ {int /*<<< orphan*/  sec; } ;
struct dvb_demux_feed {scalar_t__ state; scalar_t__ type; TYPE_2__ feed; } ;
struct dvb_demux {int feednum; int filternum; TYPE_3__* filter; struct dvb_demux_feed* feed; } ;
struct av7110 {int playing; int feeding1; scalar_t__ rec_mode; struct dvb_demux demux; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ state; TYPE_1__ filter; } ;

/* Variables and functions */
 scalar_t__ DMX_STATE_GO ; 
 scalar_t__ DMX_STATE_READY ; 
 scalar_t__ DMX_TYPE_SEC ; 
 int /*<<< orphan*/  av7110_av_start_play (struct av7110*,int) ; 
 int /*<<< orphan*/  av7110_start_feed (struct dvb_demux_feed*) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 

__attribute__((used)) static void restart_feeds(struct av7110 *av7110)
{
	struct dvb_demux *dvbdmx = &av7110->demux;
	struct dvb_demux_feed *feed;
	int mode;
	int feeding;
	int i, j;

	dprintk(4, "%p\n", av7110);

	mode = av7110->playing;
	av7110->playing = 0;
	av7110->rec_mode = 0;

	feeding = av7110->feeding1; /* full_ts mod */

	for (i = 0; i < dvbdmx->feednum; i++) {
		feed = &dvbdmx->feed[i];
		if (feed->state == DMX_STATE_GO) {
			if (feed->type == DMX_TYPE_SEC) {
				for (j = 0; j < dvbdmx->filternum; j++) {
					if (dvbdmx->filter[j].type != DMX_TYPE_SEC)
						continue;
					if (dvbdmx->filter[j].filter.parent != &feed->feed.sec)
						continue;
					if (dvbdmx->filter[j].state == DMX_STATE_GO)
						dvbdmx->filter[j].state = DMX_STATE_READY;
				}
			}
			av7110_start_feed(feed);
		}
	}

	av7110->feeding1 = feeding; /* full_ts mod */

	if (mode)
		av7110_av_start_play(av7110, mode);
}