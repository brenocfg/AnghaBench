#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xendispl_event_page {int dummy; } ;
struct xenbus_device {int /*<<< orphan*/  devicetype; int /*<<< orphan*/  otherend_id; } ;
struct xen_drm_front_info {struct xenbus_device* xb_dev; } ;
struct TYPE_6__ {struct xendispl_event_page* page; } ;
struct TYPE_8__ {int /*<<< orphan*/ * sring; } ;
struct TYPE_5__ {TYPE_4__ ring; int /*<<< orphan*/  req_io_lock; int /*<<< orphan*/  completion; } ;
struct TYPE_7__ {TYPE_2__ evt; TYPE_1__ req; } ;
struct xen_drm_front_evtchnl {int type; int index; int gref; int irq; int /*<<< orphan*/  port; TYPE_3__ u; int /*<<< orphan*/  state; struct xen_drm_front_info* front_info; } ;
struct xen_displif_sring {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;
typedef  int grant_ref_t ;
typedef  enum xen_drm_front_evtchnl_type { ____Placeholder_xen_drm_front_evtchnl_type } xen_drm_front_evtchnl_type ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EVTCHNL_STATE_DISCONNECTED ; 
 int EVTCHNL_TYPE_REQ ; 
 int /*<<< orphan*/  FRONT_RING_INIT (TYPE_4__*,struct xen_displif_sring*,int /*<<< orphan*/ ) ; 
 int GFP_NOIO ; 
 int GRANT_INVALID_REF ; 
 int /*<<< orphan*/  SHARED_RING_INIT (struct xen_displif_sring*) ; 
 int /*<<< orphan*/  XEN_PAGE_SIZE ; 
 int __GFP_HIGH ; 
 int bind_evtchn_to_irqhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xen_drm_front_evtchnl*) ; 
 int /*<<< orphan*/  evtchnl_interrupt_ctrl ; 
 int /*<<< orphan*/  evtchnl_interrupt_evt ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 unsigned long get_zeroed_page (int) ; 
 int gnttab_grant_foreign_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct xen_drm_front_evtchnl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_gfn (void*) ; 
 int xenbus_alloc_evtchn (struct xenbus_device*,int /*<<< orphan*/ *) ; 
 int xenbus_grant_ring (struct xenbus_device*,struct xen_displif_sring*,int,int*) ; 

__attribute__((used)) static int evtchnl_alloc(struct xen_drm_front_info *front_info, int index,
			 struct xen_drm_front_evtchnl *evtchnl,
			 enum xen_drm_front_evtchnl_type type)
{
	struct xenbus_device *xb_dev = front_info->xb_dev;
	unsigned long page;
	grant_ref_t gref;
	irq_handler_t handler;
	int ret;

	memset(evtchnl, 0, sizeof(*evtchnl));
	evtchnl->type = type;
	evtchnl->index = index;
	evtchnl->front_info = front_info;
	evtchnl->state = EVTCHNL_STATE_DISCONNECTED;
	evtchnl->gref = GRANT_INVALID_REF;

	page = get_zeroed_page(GFP_NOIO | __GFP_HIGH);
	if (!page) {
		ret = -ENOMEM;
		goto fail;
	}

	if (type == EVTCHNL_TYPE_REQ) {
		struct xen_displif_sring *sring;

		init_completion(&evtchnl->u.req.completion);
		mutex_init(&evtchnl->u.req.req_io_lock);
		sring = (struct xen_displif_sring *)page;
		SHARED_RING_INIT(sring);
		FRONT_RING_INIT(&evtchnl->u.req.ring, sring, XEN_PAGE_SIZE);

		ret = xenbus_grant_ring(xb_dev, sring, 1, &gref);
		if (ret < 0) {
			evtchnl->u.req.ring.sring = NULL;
			free_page(page);
			goto fail;
		}

		handler = evtchnl_interrupt_ctrl;
	} else {
		ret = gnttab_grant_foreign_access(xb_dev->otherend_id,
						  virt_to_gfn((void *)page), 0);
		if (ret < 0) {
			free_page(page);
			goto fail;
		}

		evtchnl->u.evt.page = (struct xendispl_event_page *)page;
		gref = ret;
		handler = evtchnl_interrupt_evt;
	}
	evtchnl->gref = gref;

	ret = xenbus_alloc_evtchn(xb_dev, &evtchnl->port);
	if (ret < 0)
		goto fail;

	ret = bind_evtchn_to_irqhandler(evtchnl->port,
					handler, 0, xb_dev->devicetype,
					evtchnl);
	if (ret < 0)
		goto fail;

	evtchnl->irq = ret;
	return 0;

fail:
	DRM_ERROR("Failed to allocate ring: %d\n", ret);
	return ret;
}