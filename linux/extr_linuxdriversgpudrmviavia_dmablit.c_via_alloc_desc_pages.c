#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int descriptors_per_page; int num_desc_pages; int num_desc; int /*<<< orphan*/ ** desc_pages; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ drm_via_sg_info_t ;
typedef  int /*<<< orphan*/  drm_via_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dr_via_desc_pages_alloc ; 
 int /*<<< orphan*/ ** kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
via_alloc_desc_pages(drm_via_sg_info_t *vsg)
{
	int i;

	vsg->descriptors_per_page = PAGE_SIZE / sizeof(drm_via_descriptor_t);
	vsg->num_desc_pages = (vsg->num_desc + vsg->descriptors_per_page - 1) /
		vsg->descriptors_per_page;

	if (NULL ==  (vsg->desc_pages = kcalloc(vsg->num_desc_pages, sizeof(void *), GFP_KERNEL)))
		return -ENOMEM;

	vsg->state = dr_via_desc_pages_alloc;
	for (i = 0; i < vsg->num_desc_pages; ++i) {
		if (NULL == (vsg->desc_pages[i] =
			     (drm_via_descriptor_t *) __get_free_page(GFP_KERNEL)))
			return -ENOMEM;
	}
	DRM_DEBUG("Allocated %d pages for %d descriptors.\n", vsg->num_desc_pages,
		  vsg->num_desc);
	return 0;
}