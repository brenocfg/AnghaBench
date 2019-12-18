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
typedef  size_t u16 ;
struct atl1c_tpd_ring {size_t next_to_use; size_t count; struct atl1c_buffer* buffer_info; scalar_t__ desc; } ;
struct atl1c_tpd_desc {int dummy; } ;
struct atl1c_buffer {int dummy; } ;
struct atl1c_adapter {int /*<<< orphan*/  pdev; struct atl1c_tpd_ring* tpd_ring; } ;
typedef  enum atl1c_trans_queue { ____Placeholder_atl1c_trans_queue } atl1c_trans_queue ;

/* Variables and functions */
 struct atl1c_tpd_desc* ATL1C_TPD_DESC (struct atl1c_tpd_ring*,size_t) ; 
 int /*<<< orphan*/  atl1c_clean_buffer (int /*<<< orphan*/ ,struct atl1c_buffer*) ; 
 int /*<<< orphan*/  memset (struct atl1c_tpd_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void atl1c_tx_rollback(struct atl1c_adapter *adpt,
			      struct atl1c_tpd_desc *first_tpd,
			      enum atl1c_trans_queue type)
{
	struct atl1c_tpd_ring *tpd_ring = &adpt->tpd_ring[type];
	struct atl1c_buffer *buffer_info;
	struct atl1c_tpd_desc *tpd;
	u16 first_index, index;

	first_index = first_tpd - (struct atl1c_tpd_desc *)tpd_ring->desc;
	index = first_index;
	while (index != tpd_ring->next_to_use) {
		tpd = ATL1C_TPD_DESC(tpd_ring, index);
		buffer_info = &tpd_ring->buffer_info[index];
		atl1c_clean_buffer(adpt->pdev, buffer_info);
		memset(tpd, 0, sizeof(struct atl1c_tpd_desc));
		if (++index == tpd_ring->count)
			index = 0;
	}
	tpd_ring->next_to_use = first_index;
}