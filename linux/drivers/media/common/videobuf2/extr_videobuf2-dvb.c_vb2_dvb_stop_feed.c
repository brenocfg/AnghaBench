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
struct vb2_dvb {scalar_t__ nfeeds; int /*<<< orphan*/  lock; int /*<<< orphan*/  dvbq; } ;
struct dvb_demux_feed {struct dvb_demux* demux; } ;
struct dvb_demux {struct vb2_dvb* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vb2_thread_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vb2_dvb_stop_feed(struct dvb_demux_feed *feed)
{
	struct dvb_demux *demux = feed->demux;
	struct vb2_dvb *dvb = demux->priv;
	int err = 0;

	mutex_lock(&dvb->lock);
	dvb->nfeeds--;
	if (0 == dvb->nfeeds)
		err = vb2_thread_stop(&dvb->dvbq);
	mutex_unlock(&dvb->lock);
	return err;
}