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
typedef  size_t u8 ;
struct hfi1_vnic_vport_info {struct hfi1_vnic_sdma* sdma; } ;
struct hfi1_vnic_sdma {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ HFI1_VNIC_SDMA_Q_ACTIVE ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 

inline bool hfi1_vnic_sdma_write_avail(struct hfi1_vnic_vport_info *vinfo,
				       u8 q_idx)
{
	struct hfi1_vnic_sdma *vnic_sdma = &vinfo->sdma[q_idx];

	return (READ_ONCE(vnic_sdma->state) == HFI1_VNIC_SDMA_Q_ACTIVE);
}