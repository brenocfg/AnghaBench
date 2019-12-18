#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; TYPE_1__* dev; } ;
struct uwb_rsv {int /*<<< orphan*/  stream; TYPE_2__ target; struct uwb_rc* rc; } ;
struct device {int dummy; } ;
struct TYPE_6__ {unsigned long* streams; struct device dev; } ;
struct uwb_rc {TYPE_3__ uwb_dev; } ;
struct TYPE_4__ {unsigned long* streams; } ;

/* Variables and functions */
#define  UWB_RSV_TARGET_DEV 129 
#define  UWB_RSV_TARGET_DEVADDR 128 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uwb_rsv_put_stream(struct uwb_rsv *rsv)
{
	struct uwb_rc *rc = rsv->rc;
	struct device *dev = &rc->uwb_dev.dev;
	unsigned long *streams_bm;

	switch (rsv->target.type) {
	case UWB_RSV_TARGET_DEV:
		streams_bm = rsv->target.dev->streams;
		break;
	case UWB_RSV_TARGET_DEVADDR:
		streams_bm = rc->uwb_dev.streams;
		break;
	default:
		return;
	}

	clear_bit(rsv->stream, streams_bm);

	dev_dbg(dev, "put stream %d\n", rsv->stream);
}