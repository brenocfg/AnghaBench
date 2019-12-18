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
struct bnxt_ring_mem_info {int depth; int /*<<< orphan*/ * dma_arr; int /*<<< orphan*/  pg_tbl_map; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int BNXT_PAGE_SHIFT ; 
 int BNXT_PAGE_SIZE ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_hwrm_set_pg_attr(struct bnxt_ring_mem_info *rmem, u8 *pg_attr,
				  __le64 *pg_dir)
{
	u8 pg_size = 0;

	if (BNXT_PAGE_SHIFT == 13)
		pg_size = 1 << 4;
	else if (BNXT_PAGE_SIZE == 16)
		pg_size = 2 << 4;

	*pg_attr = pg_size;
	if (rmem->depth >= 1) {
		if (rmem->depth == 2)
			*pg_attr |= 2;
		else
			*pg_attr |= 1;
		*pg_dir = cpu_to_le64(rmem->pg_tbl_map);
	} else {
		*pg_dir = cpu_to_le64(rmem->dma_arr[0]);
	}
}