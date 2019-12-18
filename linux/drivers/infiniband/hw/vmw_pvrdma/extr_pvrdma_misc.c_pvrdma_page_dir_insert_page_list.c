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
typedef  int /*<<< orphan*/  u64 ;
struct pvrdma_page_dir {int npages; } ;

/* Variables and functions */
 int EINVAL ; 
 int pvrdma_page_dir_insert_dma (struct pvrdma_page_dir*,int,int /*<<< orphan*/ ) ; 

int pvrdma_page_dir_insert_page_list(struct pvrdma_page_dir *pdir,
				     u64 *page_list,
				     int num_pages)
{
	int i;
	int ret;

	if (num_pages > pdir->npages)
		return -EINVAL;

	for (i = 0; i < num_pages; i++) {
		ret = pvrdma_page_dir_insert_dma(pdir, i, page_list[i]);
		if (ret)
			return ret;
	}

	return 0;
}