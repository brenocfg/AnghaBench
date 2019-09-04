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
struct dvb_demux {int /*<<< orphan*/  mutex; } ;
struct dmx_frontend {int dummy; } ;
struct dmx_demux {struct dmx_frontend* frontend; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvbdmx_connect_frontend(struct dmx_demux *demux,
				   struct dmx_frontend *frontend)
{
	struct dvb_demux *dvbdemux = (struct dvb_demux *)demux;

	if (demux->frontend)
		return -EINVAL;

	mutex_lock(&dvbdemux->mutex);

	demux->frontend = frontend;
	mutex_unlock(&dvbdemux->mutex);
	return 0;
}