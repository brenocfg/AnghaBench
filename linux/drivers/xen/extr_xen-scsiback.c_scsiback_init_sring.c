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
struct vscsiif_sring {int dummy; } ;
struct vscsibk_info {int irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  domid; int /*<<< orphan*/  ring; } ;
typedef  int /*<<< orphan*/  grant_ref_t ;
typedef  int /*<<< orphan*/  evtchn_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  BACK_RING_INIT (int /*<<< orphan*/ *,struct vscsiif_sring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int bind_interdomain_evtchn_to_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct vscsibk_info*) ; 
 int /*<<< orphan*/  scsiback_irq_fn ; 
 int /*<<< orphan*/  unbind_from_irqhandler (int,struct vscsibk_info*) ; 
 int xenbus_map_ring_valloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void**) ; 
 int /*<<< orphan*/  xenbus_unmap_ring_vfree (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int scsiback_init_sring(struct vscsibk_info *info, grant_ref_t ring_ref,
			evtchn_port_t evtchn)
{
	void *area;
	struct vscsiif_sring *sring;
	int err;

	if (info->irq)
		return -1;

	err = xenbus_map_ring_valloc(info->dev, &ring_ref, 1, &area);
	if (err)
		return err;

	sring = (struct vscsiif_sring *)area;
	BACK_RING_INIT(&info->ring, sring, PAGE_SIZE);

	err = bind_interdomain_evtchn_to_irq(info->domid, evtchn);
	if (err < 0)
		goto unmap_page;

	info->irq = err;

	err = request_threaded_irq(info->irq, NULL, scsiback_irq_fn,
				   IRQF_ONESHOT, "vscsiif-backend", info);
	if (err)
		goto free_irq;

	return 0;

free_irq:
	unbind_from_irqhandler(info->irq, info);
	info->irq = 0;
unmap_page:
	xenbus_unmap_ring_vfree(info->dev, area);

	return err;
}