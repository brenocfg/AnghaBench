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
typedef  scalar_t__ u64 ;
struct sq_hdr_subdesc {int subdesc_cnt; int tot_len; int post_cqe; int /*<<< orphan*/  subdesc_type; } ;
struct snd_queue {scalar_t__* xdp_page; } ;

/* Variables and functions */
 scalar_t__ GET_SQ_DESC (struct snd_queue*,int) ; 
 int /*<<< orphan*/  SND_QUEUE_DESC_SIZE ; 
 int /*<<< orphan*/  SQ_DESC_TYPE_HEADER ; 
 int /*<<< orphan*/  memset (struct sq_hdr_subdesc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ virt_to_page (void*) ; 

__attribute__((used)) static inline void
nicvf_xdp_sq_add_hdr_subdesc(struct snd_queue *sq, int qentry,
			     int subdesc_cnt, u64 data, int len)
{
	struct sq_hdr_subdesc *hdr;

	hdr = (struct sq_hdr_subdesc *)GET_SQ_DESC(sq, qentry);
	memset(hdr, 0, SND_QUEUE_DESC_SIZE);
	hdr->subdesc_type = SQ_DESC_TYPE_HEADER;
	hdr->subdesc_cnt = subdesc_cnt;
	hdr->tot_len = len;
	hdr->post_cqe = 1;
	sq->xdp_page[qentry] = (u64)virt_to_page((void *)data);
}