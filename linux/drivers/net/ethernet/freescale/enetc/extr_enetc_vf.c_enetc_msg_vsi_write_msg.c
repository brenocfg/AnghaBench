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
typedef  int u32 ;
struct enetc_msg_swbd {int /*<<< orphan*/  dma; int /*<<< orphan*/  size; } ;
struct enetc_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_VSIMSGSNDAR0 ; 
 int /*<<< orphan*/  ENETC_VSIMSGSNDAR1 ; 
 int enetc_vsi_set_msize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_wr (struct enetc_hw*,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enetc_msg_vsi_write_msg(struct enetc_hw *hw,
				    struct enetc_msg_swbd *msg)
{
	u32 val;

	val = enetc_vsi_set_msize(msg->size) | lower_32_bits(msg->dma);
	enetc_wr(hw, ENETC_VSIMSGSNDAR1, upper_32_bits(msg->dma));
	enetc_wr(hw, ENETC_VSIMSGSNDAR0, val);
}