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
struct TYPE_2__ {int capabilities; } ;
struct dvb_demux {int filternum; int feednum; int (* start_feed ) (struct dvb_demux_feed*) ;int (* stop_feed ) (struct dvb_demux_feed*) ;TYPE_1__ dmx; int /*<<< orphan*/ * write_to_decoder; void* priv; } ;

/* Variables and functions */
 int DMX_MEMORY_BASED_FILTERING ; 
 int DMX_SECTION_FILTERING ; 
 int DMX_TS_FILTERING ; 
 int dvb_dmx_init (struct dvb_demux*) ; 

int my_dvb_dmx_ts_card_init(struct dvb_demux *dvbdemux, char *id,
			    int (*start_feed)(struct dvb_demux_feed *),
			    int (*stop_feed)(struct dvb_demux_feed *),
			    void *priv)
{
	dvbdemux->priv = priv;

	dvbdemux->filternum = 256;
	dvbdemux->feednum = 256;
	dvbdemux->start_feed = start_feed;
	dvbdemux->stop_feed = stop_feed;
	dvbdemux->write_to_decoder = NULL;
	dvbdemux->dmx.capabilities = (DMX_TS_FILTERING |
				      DMX_SECTION_FILTERING |
				      DMX_MEMORY_BASED_FILTERING);
	return dvb_dmx_init(dvbdemux);
}