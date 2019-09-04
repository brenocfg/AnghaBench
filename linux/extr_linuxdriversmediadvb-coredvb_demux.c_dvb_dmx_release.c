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
struct dvb_demux {int /*<<< orphan*/  feed; int /*<<< orphan*/  filter; int /*<<< orphan*/  cnt_storage; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void dvb_dmx_release(struct dvb_demux *dvbdemux)
{
	vfree(dvbdemux->cnt_storage);
	vfree(dvbdemux->filter);
	vfree(dvbdemux->feed);
}