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
struct drm_master {int /*<<< orphan*/  lessee_idr; int /*<<< orphan*/  leases; int /*<<< orphan*/  lessee_list; int /*<<< orphan*/  lessees; struct drm_device* dev; int /*<<< orphan*/  magic_map; int /*<<< orphan*/  refcount; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_master_legacy_init (struct drm_master*) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct drm_master* kzalloc (int,int /*<<< orphan*/ ) ; 

struct drm_master *drm_master_create(struct drm_device *dev)
{
	struct drm_master *master;

	master = kzalloc(sizeof(*master), GFP_KERNEL);
	if (!master)
		return NULL;

	kref_init(&master->refcount);
	drm_master_legacy_init(master);
	idr_init(&master->magic_map);
	master->dev = dev;

	/* initialize the tree of output resource lessees */
	INIT_LIST_HEAD(&master->lessees);
	INIT_LIST_HEAD(&master->lessee_list);
	idr_init(&master->leases);
	idr_init(&master->lessee_idr);

	return master;
}