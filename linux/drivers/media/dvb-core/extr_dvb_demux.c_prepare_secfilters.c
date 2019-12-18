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
typedef  int u8 ;
struct dmx_section_filter {int* filter_mode; int* filter_mask; } ;
struct dvb_demux_filter {int* maskandmode; int* maskandnotmode; int doneq; struct dmx_section_filter filter; struct dvb_demux_filter* next; } ;
struct dvb_demux_feed {struct dvb_demux_filter* filter; } ;

/* Variables and functions */
 int DVB_DEMUX_MASK_MAX ; 

__attribute__((used)) static void prepare_secfilters(struct dvb_demux_feed *dvbdmxfeed)
{
	int i;
	struct dvb_demux_filter *f;
	struct dmx_section_filter *sf;
	u8 mask, mode, doneq;

	if (!(f = dvbdmxfeed->filter))
		return;
	do {
		sf = &f->filter;
		doneq = false;
		for (i = 0; i < DVB_DEMUX_MASK_MAX; i++) {
			mode = sf->filter_mode[i];
			mask = sf->filter_mask[i];
			f->maskandmode[i] = mask & mode;
			doneq |= f->maskandnotmode[i] = mask & ~mode;
		}
		f->doneq = doneq ? true : false;
	} while ((f = f->next));
}