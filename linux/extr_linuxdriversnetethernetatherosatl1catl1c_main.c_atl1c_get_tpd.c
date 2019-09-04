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
typedef  scalar_t__ u16 ;
struct atl1c_tpd_ring {scalar_t__ next_to_use; scalar_t__ count; } ;
struct atl1c_tpd_desc {int dummy; } ;
struct atl1c_adapter {struct atl1c_tpd_ring* tpd_ring; } ;
typedef  enum atl1c_trans_queue { ____Placeholder_atl1c_trans_queue } atl1c_trans_queue ;

/* Variables and functions */
 struct atl1c_tpd_desc* ATL1C_TPD_DESC (struct atl1c_tpd_ring*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct atl1c_tpd_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct atl1c_tpd_desc *atl1c_get_tpd(struct atl1c_adapter *adapter,
	enum atl1c_trans_queue type)
{
	struct atl1c_tpd_ring *tpd_ring = &adapter->tpd_ring[type];
	struct atl1c_tpd_desc *tpd_desc;
	u16 next_to_use = 0;

	next_to_use = tpd_ring->next_to_use;
	if (++tpd_ring->next_to_use == tpd_ring->count)
		tpd_ring->next_to_use = 0;
	tpd_desc = ATL1C_TPD_DESC(tpd_ring, next_to_use);
	memset(tpd_desc, 0, sizeof(struct atl1c_tpd_desc));
	return	tpd_desc;
}