#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ts; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* ts ) (unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct dvb_demux_feed {TYPE_2__ feed; TYPE_1__ cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvb_filter_pes2ts_cb(void *priv, unsigned char *data)
{
	struct dvb_demux_feed *dvbdmxfeed = (struct dvb_demux_feed *) priv;

	dvbdmxfeed->cb.ts(data, 188, NULL, 0,
			  &dvbdmxfeed->feed.ts, NULL);
	return 0;
}