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
struct xgene_enet_raw_desc16 {int /*<<< orphan*/  m0; } ;
struct xgene_enet_desc_ring {int slots; int dst_ring_num; struct xgene_enet_raw_desc16* raw_desc16; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPQNUM ; 
 int SET_VAL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STASH ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 

__attribute__((used)) static void xgene_enet_init_bufpool(struct xgene_enet_desc_ring *buf_pool)
{
	struct xgene_enet_raw_desc16 *raw_desc;
	int i;

	if (!buf_pool)
		return;

	for (i = 0; i < buf_pool->slots; i++) {
		raw_desc = &buf_pool->raw_desc16[i];

		/* Hardware expects descriptor in little endian format */
		raw_desc->m0 = cpu_to_le64(i |
				SET_VAL(FPQNUM, buf_pool->dst_ring_num) |
				SET_VAL(STASH, 3));
	}
}