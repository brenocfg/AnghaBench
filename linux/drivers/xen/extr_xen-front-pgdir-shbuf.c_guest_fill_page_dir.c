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
struct xen_page_directory {int /*<<< orphan*/  gref; int /*<<< orphan*/  gref_dir_next_page; } ;
struct xen_front_pgdir_shbuf {unsigned char* directory; int num_pages; int /*<<< orphan*/ * grefs; } ;
typedef  int /*<<< orphan*/  grant_ref_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRANT_INVALID_REF ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int XEN_NUM_GREFS_PER_PAGE ; 
 int get_num_pages_dir (struct xen_front_pgdir_shbuf*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void guest_fill_page_dir(struct xen_front_pgdir_shbuf *buf)
{
	unsigned char *ptr;
	int cur_gref, grefs_left, to_copy, i, num_pages_dir;

	ptr = buf->directory;
	num_pages_dir = get_num_pages_dir(buf);

	/*
	 * While copying, skip grefs at start, they are for pages
	 * granted for the page directory itself.
	 */
	cur_gref = num_pages_dir;
	grefs_left = buf->num_pages;
	for (i = 0; i < num_pages_dir; i++) {
		struct xen_page_directory *page_dir =
			(struct xen_page_directory *)ptr;

		if (grefs_left <= XEN_NUM_GREFS_PER_PAGE) {
			to_copy = grefs_left;
			page_dir->gref_dir_next_page = GRANT_INVALID_REF;
		} else {
			to_copy = XEN_NUM_GREFS_PER_PAGE;
			page_dir->gref_dir_next_page = buf->grefs[i + 1];
		}
		memcpy(&page_dir->gref, &buf->grefs[cur_gref],
		       to_copy * sizeof(grant_ref_t));
		ptr += PAGE_SIZE;
		grefs_left -= to_copy;
		cur_gref += to_copy;
	}
}