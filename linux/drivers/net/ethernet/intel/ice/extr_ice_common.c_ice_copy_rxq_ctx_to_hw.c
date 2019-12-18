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
typedef  int /*<<< orphan*/  u32 ;
struct ice_hw {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_DBG_QCTX ; 
 int ICE_ERR_BAD_PTR ; 
 int ICE_ERR_PARAM ; 
 int ICE_RXQ_CTX_SIZE_DWORDS ; 
 int /*<<< orphan*/  QRX_CONTEXT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QRX_CTRL_MAX_INDEX ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_copy_rxq_ctx_to_hw(struct ice_hw *hw, u8 *ice_rxq_ctx, u32 rxq_index)
{
	u8 i;

	if (!ice_rxq_ctx)
		return ICE_ERR_BAD_PTR;

	if (rxq_index > QRX_CTRL_MAX_INDEX)
		return ICE_ERR_PARAM;

	/* Copy each dword separately to HW */
	for (i = 0; i < ICE_RXQ_CTX_SIZE_DWORDS; i++) {
		wr32(hw, QRX_CONTEXT(i, rxq_index),
		     *((u32 *)(ice_rxq_ctx + (i * sizeof(u32)))));

		ice_debug(hw, ICE_DBG_QCTX, "qrxdata[%d]: %08X\n", i,
			  *((u32 *)(ice_rxq_ctx + (i * sizeof(u32)))));
	}

	return 0;
}