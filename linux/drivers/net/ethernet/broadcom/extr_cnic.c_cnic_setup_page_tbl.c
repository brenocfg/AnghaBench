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
typedef  int u64 ;
struct cnic_dma {int num_pages; int* pg_map_arr; scalar_t__ pgtbl; } ;
struct cnic_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static void cnic_setup_page_tbl(struct cnic_dev *dev, struct cnic_dma *dma)
{
	int i;
	__le32 *page_table = (__le32 *) dma->pgtbl;

	for (i = 0; i < dma->num_pages; i++) {
		/* Each entry needs to be in big endian format. */
		*page_table = cpu_to_le32((u64) dma->pg_map_arr[i] >> 32);
		page_table++;
		*page_table = cpu_to_le32(dma->pg_map_arr[i] & 0xffffffff);
		page_table++;
	}
}