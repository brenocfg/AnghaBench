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
struct xen_page_directory {int /*<<< orphan*/  gref_dir_next_page; } ;
struct xen_front_pgdir_shbuf {unsigned char* directory; int /*<<< orphan*/ * grefs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRANT_INVALID_REF ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int get_num_pages_dir (struct xen_front_pgdir_shbuf*) ; 

__attribute__((used)) static void backend_fill_page_dir(struct xen_front_pgdir_shbuf *buf)
{
	struct xen_page_directory *page_dir;
	unsigned char *ptr;
	int i, num_pages_dir;

	ptr = buf->directory;
	num_pages_dir = get_num_pages_dir(buf);

	/* Fill only grefs for the page directory itself. */
	for (i = 0; i < num_pages_dir - 1; i++) {
		page_dir = (struct xen_page_directory *)ptr;

		page_dir->gref_dir_next_page = buf->grefs[i + 1];
		ptr += PAGE_SIZE;
	}
	/* Last page must say there is no more pages. */
	page_dir = (struct xen_page_directory *)ptr;
	page_dir->gref_dir_next_page = GRANT_INVALID_REF;
}