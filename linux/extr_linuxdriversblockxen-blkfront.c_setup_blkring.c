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
struct xenbus_device {int dummy; } ;
struct blkif_sring {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sring; } ;
struct blkfront_ring_info {int irq; int /*<<< orphan*/  evtchn; int /*<<< orphan*/ * ring_ref; TYPE_1__ ring; struct blkfront_info* dev_info; } ;
struct blkfront_info {unsigned long nr_ring_pages; } ;
typedef  int /*<<< orphan*/  grant_ref_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FRONT_RING_INIT (TYPE_1__*,struct blkif_sring*,unsigned long) ; 
 int GFP_NOIO ; 
 int /*<<< orphan*/  GRANT_INVALID_REF ; 
 int /*<<< orphan*/  SHARED_RING_INIT (struct blkif_sring*) ; 
 int XENBUS_MAX_RING_GRANTS ; 
 unsigned long XEN_PAGE_SIZE ; 
 int __GFP_HIGH ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 int bind_evtchn_to_irqhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct blkfront_ring_info*) ; 
 int /*<<< orphan*/  blkif_free (struct blkfront_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkif_interrupt ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (unsigned long) ; 
 int xenbus_alloc_evtchn (struct xenbus_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*) ; 
 int xenbus_grant_ring (struct xenbus_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setup_blkring(struct xenbus_device *dev,
			 struct blkfront_ring_info *rinfo)
{
	struct blkif_sring *sring;
	int err, i;
	struct blkfront_info *info = rinfo->dev_info;
	unsigned long ring_size = info->nr_ring_pages * XEN_PAGE_SIZE;
	grant_ref_t gref[XENBUS_MAX_RING_GRANTS];

	for (i = 0; i < info->nr_ring_pages; i++)
		rinfo->ring_ref[i] = GRANT_INVALID_REF;

	sring = (struct blkif_sring *)__get_free_pages(GFP_NOIO | __GFP_HIGH,
						       get_order(ring_size));
	if (!sring) {
		xenbus_dev_fatal(dev, -ENOMEM, "allocating shared ring");
		return -ENOMEM;
	}
	SHARED_RING_INIT(sring);
	FRONT_RING_INIT(&rinfo->ring, sring, ring_size);

	err = xenbus_grant_ring(dev, rinfo->ring.sring, info->nr_ring_pages, gref);
	if (err < 0) {
		free_pages((unsigned long)sring, get_order(ring_size));
		rinfo->ring.sring = NULL;
		goto fail;
	}
	for (i = 0; i < info->nr_ring_pages; i++)
		rinfo->ring_ref[i] = gref[i];

	err = xenbus_alloc_evtchn(dev, &rinfo->evtchn);
	if (err)
		goto fail;

	err = bind_evtchn_to_irqhandler(rinfo->evtchn, blkif_interrupt, 0,
					"blkif", rinfo);
	if (err <= 0) {
		xenbus_dev_fatal(dev, err,
				 "bind_evtchn_to_irqhandler failed");
		goto fail;
	}
	rinfo->irq = err;

	return 0;
fail:
	blkif_free(info, 0);
	return err;
}