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
struct dvb_demux_feed {struct dvb_demux* demux; } ;
struct dvb_demux {struct av7110* priv; } ;
struct av7110 {int /*<<< orphan*/  feedlock1; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stop_ts_capture (struct av7110*) ; 

__attribute__((used)) static int budget_stop_feed(struct dvb_demux_feed *feed)
{
	struct dvb_demux *demux = feed->demux;
	struct av7110 *budget = demux->priv;
	int status;

	dprintk(2, "budget: %p\n", budget);

	spin_lock(&budget->feedlock1);
	status = stop_ts_capture(budget);
	spin_unlock(&budget->feedlock1);
	return status;
}