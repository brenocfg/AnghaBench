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
typedef  int u8 ;
struct drm_dp_mst_branch {int lct; int /*<<< orphan*/  malloc_kref; int /*<<< orphan*/  topology_kref; int /*<<< orphan*/  ports; int /*<<< orphan*/  rad; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct drm_dp_mst_branch* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static struct drm_dp_mst_branch *drm_dp_add_mst_branch_device(u8 lct, u8 *rad)
{
	struct drm_dp_mst_branch *mstb;

	mstb = kzalloc(sizeof(*mstb), GFP_KERNEL);
	if (!mstb)
		return NULL;

	mstb->lct = lct;
	if (lct > 1)
		memcpy(mstb->rad, rad, lct / 2);
	INIT_LIST_HEAD(&mstb->ports);
	kref_init(&mstb->topology_kref);
	kref_init(&mstb->malloc_kref);
	return mstb;
}