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
struct xenbus_transaction {int dummy; } ;
struct xenbus_device {int dummy; } ;
struct xen_drm_front_evtchnl {int /*<<< orphan*/  port; int /*<<< orphan*/  gref; TYPE_1__* front_info; } ;
struct TYPE_2__ {struct xenbus_device* xb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  xenbus_dev_error (struct xenbus_device*,int,char*) ; 
 int xenbus_printf (struct xenbus_transaction,char const*,char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int evtchnl_publish(struct xenbus_transaction xbt,
			   struct xen_drm_front_evtchnl *evtchnl,
			   const char *path, const char *node_ring,
			   const char *node_chnl)
{
	struct xenbus_device *xb_dev = evtchnl->front_info->xb_dev;
	int ret;

	/* write control channel ring reference */
	ret = xenbus_printf(xbt, path, node_ring, "%u", evtchnl->gref);
	if (ret < 0) {
		xenbus_dev_error(xb_dev, ret, "writing ring-ref");
		return ret;
	}

	/* write event channel ring reference */
	ret = xenbus_printf(xbt, path, node_chnl, "%u", evtchnl->port);
	if (ret < 0) {
		xenbus_dev_error(xb_dev, ret, "writing event channel");
		return ret;
	}

	return 0;
}