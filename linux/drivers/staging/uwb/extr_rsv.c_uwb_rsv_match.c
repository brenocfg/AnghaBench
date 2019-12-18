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
struct uwb_rsv {int stream; TYPE_2__ target; TYPE_3__* owner; } ;
struct uwb_ie_drp {int dummy; } ;
struct uwb_dev_addr {int dummy; } ;
struct uwb_dev {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_6__ {struct uwb_dev_addr dev_addr; } ;
struct TYPE_4__ {struct uwb_dev_addr dev_addr; } ;

/* Variables and functions */
#define  UWB_RSV_TARGET_DEV 129 
#define  UWB_RSV_TARGET_DEVADDR 128 
 int /*<<< orphan*/  uwb_dev_addr_cmp (int /*<<< orphan*/ *,struct uwb_dev_addr*) ; 
 int /*<<< orphan*/  uwb_ie_drp_owner (struct uwb_ie_drp*) ; 
 int uwb_ie_drp_stream_index (struct uwb_ie_drp*) ; 

__attribute__((used)) static bool uwb_rsv_match(struct uwb_rsv *rsv, struct uwb_dev *src,
			  struct uwb_ie_drp *drp_ie)
{
	struct uwb_dev_addr *rsv_src;
	int stream;

	stream = uwb_ie_drp_stream_index(drp_ie);

	if (rsv->stream != stream)
		return false;

	switch (rsv->target.type) {
	case UWB_RSV_TARGET_DEVADDR:
		return rsv->stream == stream;
	case UWB_RSV_TARGET_DEV:
		if (uwb_ie_drp_owner(drp_ie))
			rsv_src = &rsv->owner->dev_addr;
		else
			rsv_src = &rsv->target.dev->dev_addr;
		return uwb_dev_addr_cmp(&src->dev_addr, rsv_src) == 0;
	}
	return false;
}