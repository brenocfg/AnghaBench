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
struct dvb_demux_feed {struct dvb_demux* demux; } ;
struct dvb_demux {struct ddb_input* priv; } ;
struct ddb_input {int nr; TYPE_1__* port; } ;
struct ddb_dvb {int users; } ;
struct TYPE_2__ {struct ddb_dvb* dvb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ddb_input_stop_all (struct ddb_input*) ; 

__attribute__((used)) static int stop_feed(struct dvb_demux_feed *dvbdmxfeed)
{
	struct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	struct ddb_input *input = dvbdmx->priv;
	struct ddb_dvb *dvb = &input->port->dvb[input->nr & 1];

	if (--dvb->users)
		return dvb->users;

	ddb_input_stop_all(input);
	return 0;
}