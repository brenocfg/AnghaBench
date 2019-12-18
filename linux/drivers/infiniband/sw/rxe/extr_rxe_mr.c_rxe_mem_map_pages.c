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
typedef  void* u64 ;
struct rxe_phys_buf {int size; int /*<<< orphan*/  addr; } ;
struct rxe_mem {int max_buf; int page_shift; int length; int /*<<< orphan*/  state; void* va; void* iova; struct rxe_map** map; } ;
struct rxe_map {struct rxe_phys_buf* buf; } ;
struct rxe_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int RXE_BUF_PER_MAP ; 
 int /*<<< orphan*/  RXE_MEM_STATE_VALID ; 

int rxe_mem_map_pages(struct rxe_dev *rxe, struct rxe_mem *mem,
		      u64 *page, int num_pages, u64 iova)
{
	int i;
	int num_buf;
	int err;
	struct rxe_map **map;
	struct rxe_phys_buf *buf;
	int page_size;

	if (num_pages > mem->max_buf) {
		err = -EINVAL;
		goto err1;
	}

	num_buf		= 0;
	page_size	= 1 << mem->page_shift;
	map		= mem->map;
	buf		= map[0]->buf;

	for (i = 0; i < num_pages; i++) {
		buf->addr = *page++;
		buf->size = page_size;
		buf++;
		num_buf++;

		if (num_buf == RXE_BUF_PER_MAP) {
			map++;
			buf = map[0]->buf;
			num_buf = 0;
		}
	}

	mem->iova	= iova;
	mem->va		= iova;
	mem->length	= num_pages << mem->page_shift;
	mem->state	= RXE_MEM_STATE_VALID;

	return 0;

err1:
	return err;
}