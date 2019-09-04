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
struct xen_drm_front_shbuf {int num_pages; struct gnttab_unmap_grant_ref* backend_map_handles; int /*<<< orphan*/ * pages; int /*<<< orphan*/  grefs; } ;
struct gnttab_unmap_grant_ref {scalar_t__ status; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GNTMAP_host_map ; 
 scalar_t__ GNTST_okay ; 
 int /*<<< orphan*/  gnttab_set_unmap_op (struct gnttab_unmap_grant_ref*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gnttab_unmap_grant_ref) ; 
 int gnttab_unmap_refs (struct gnttab_unmap_grant_ref*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct gnttab_unmap_grant_ref* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gnttab_unmap_grant_ref*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xen_page_to_vaddr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int backend_unmap(struct xen_drm_front_shbuf *buf)
{
	struct gnttab_unmap_grant_ref *unmap_ops;
	int i, ret;

	if (!buf->pages || !buf->backend_map_handles || !buf->grefs)
		return 0;

	unmap_ops = kcalloc(buf->num_pages, sizeof(*unmap_ops),
			    GFP_KERNEL);
	if (!unmap_ops) {
		DRM_ERROR("Failed to get memory while unmapping\n");
		return -ENOMEM;
	}

	for (i = 0; i < buf->num_pages; i++) {
		phys_addr_t addr;

		addr = xen_page_to_vaddr(buf->pages[i]);
		gnttab_set_unmap_op(&unmap_ops[i], addr, GNTMAP_host_map,
				    buf->backend_map_handles[i]);
	}

	ret = gnttab_unmap_refs(unmap_ops, NULL, buf->pages,
				buf->num_pages);

	for (i = 0; i < buf->num_pages; i++) {
		if (unlikely(unmap_ops[i].status != GNTST_okay))
			DRM_ERROR("Failed to unmap page %d: %d\n",
				  i, unmap_ops[i].status);
	}

	if (ret)
		DRM_ERROR("Failed to unmap grant references, ret %d", ret);

	kfree(unmap_ops);
	kfree(buf->backend_map_handles);
	buf->backend_map_handles = NULL;
	return ret;
}