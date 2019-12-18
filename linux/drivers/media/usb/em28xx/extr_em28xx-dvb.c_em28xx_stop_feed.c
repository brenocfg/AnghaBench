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
struct em28xx_dvb {int /*<<< orphan*/  lock; int /*<<< orphan*/  nfeeds; } ;
struct dvb_demux_feed {struct dvb_demux* demux; } ;
struct dvb_demux {struct em28xx_dvb* priv; } ;

/* Variables and functions */
 int em28xx_stop_streaming (struct em28xx_dvb*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int em28xx_stop_feed(struct dvb_demux_feed *feed)
{
	struct dvb_demux *demux  = feed->demux;
	struct em28xx_dvb *dvb = demux->priv;
	int err = 0;

	mutex_lock(&dvb->lock);
	dvb->nfeeds--;

	if (!dvb->nfeeds)
		err = em28xx_stop_streaming(dvb);

	mutex_unlock(&dvb->lock);
	return err;
}