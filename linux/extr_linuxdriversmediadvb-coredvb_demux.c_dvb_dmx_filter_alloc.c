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
struct dvb_demux_filter {scalar_t__ state; } ;
struct dvb_demux {int filternum; struct dvb_demux_filter* filter; } ;

/* Variables and functions */
 scalar_t__ DMX_STATE_ALLOCATED ; 
 scalar_t__ DMX_STATE_FREE ; 

__attribute__((used)) static struct dvb_demux_filter *dvb_dmx_filter_alloc(struct dvb_demux *demux)
{
	int i;

	for (i = 0; i < demux->filternum; i++)
		if (demux->filter[i].state == DMX_STATE_FREE)
			break;

	if (i == demux->filternum)
		return NULL;

	demux->filter[i].state = DMX_STATE_ALLOCATED;

	return &demux->filter[i];
}