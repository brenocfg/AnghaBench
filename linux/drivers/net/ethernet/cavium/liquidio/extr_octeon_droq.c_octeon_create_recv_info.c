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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
typedef  void* u16 ;
struct octeon_skb_page_info {scalar_t__ dma; int /*<<< orphan*/ * page; } ;
struct octeon_recv_pkt {size_t length; size_t* buffer_size; int /*<<< orphan*/ ** buffer_ptr; void* octeon_id; void* buffer_count; int /*<<< orphan*/  rh; } ;
struct octeon_recv_info {struct octeon_recv_pkt* recv_pkt; } ;
struct octeon_droq_info {scalar_t__ length; int /*<<< orphan*/  rh; } ;
struct octeon_droq {size_t buffer_size; int /*<<< orphan*/  max_count; TYPE_1__* recv_buf_list; } ;
struct octeon_device {int /*<<< orphan*/  pci_dev; scalar_t__ octeon_id; } ;
struct __dispatch {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * buffer; struct octeon_skb_page_info pg_info; scalar_t__ data; } ;

/* Variables and functions */
 size_t incr_index (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_unmap_ring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct octeon_recv_info* octeon_alloc_recv_info (int) ; 

__attribute__((used)) static inline struct octeon_recv_info *octeon_create_recv_info(
		struct octeon_device *octeon_dev,
		struct octeon_droq *droq,
		u32 buf_cnt,
		u32 idx)
{
	struct octeon_droq_info *info;
	struct octeon_recv_pkt *recv_pkt;
	struct octeon_recv_info *recv_info;
	u32 i, bytes_left;
	struct octeon_skb_page_info *pg_info;

	info = (struct octeon_droq_info *)droq->recv_buf_list[idx].data;

	recv_info = octeon_alloc_recv_info(sizeof(struct __dispatch));
	if (!recv_info)
		return NULL;

	recv_pkt = recv_info->recv_pkt;
	recv_pkt->rh = info->rh;
	recv_pkt->length = (u32)info->length;
	recv_pkt->buffer_count = (u16)buf_cnt;
	recv_pkt->octeon_id = (u16)octeon_dev->octeon_id;

	i = 0;
	bytes_left = (u32)info->length;

	while (buf_cnt) {
		{
			pg_info = &droq->recv_buf_list[idx].pg_info;

			lio_unmap_ring(octeon_dev->pci_dev,
				       (u64)pg_info->dma);
			pg_info->page = NULL;
			pg_info->dma = 0;
		}

		recv_pkt->buffer_size[i] =
			(bytes_left >=
			 droq->buffer_size) ? droq->buffer_size : bytes_left;

		recv_pkt->buffer_ptr[i] = droq->recv_buf_list[idx].buffer;
		droq->recv_buf_list[idx].buffer = NULL;

		idx = incr_index(idx, 1, droq->max_count);
		bytes_left -= droq->buffer_size;
		i++;
		buf_cnt--;
	}

	return recv_info;
}