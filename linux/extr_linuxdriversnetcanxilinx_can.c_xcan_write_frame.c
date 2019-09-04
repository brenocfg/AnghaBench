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
struct xcan_priv {int /*<<< orphan*/  (* write_reg ) (struct xcan_priv*,int /*<<< orphan*/ ,int) ;} ;
struct sk_buff {scalar_t__ data; } ;
struct can_frame {int can_id; int can_dlc; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_EFF_ID_BITS ; 
 int CAN_EFF_MASK ; 
 int CAN_RTR_FLAG ; 
 int CAN_SFF_ID_BITS ; 
 int CAN_SFF_MASK ; 
 int XCAN_DLCR_DLC_SHIFT ; 
 int /*<<< orphan*/  XCAN_FRAME_DLC_OFFSET (int) ; 
 int /*<<< orphan*/  XCAN_FRAME_DW1_OFFSET (int) ; 
 int /*<<< orphan*/  XCAN_FRAME_DW2_OFFSET (int) ; 
 int /*<<< orphan*/  XCAN_FRAME_ID_OFFSET (int) ; 
 int XCAN_IDR_ID1_MASK ; 
 int XCAN_IDR_ID1_SHIFT ; 
 int XCAN_IDR_ID2_MASK ; 
 int XCAN_IDR_ID2_SHIFT ; 
 int XCAN_IDR_IDE_MASK ; 
 int XCAN_IDR_RTR_MASK ; 
 int XCAN_IDR_SRR_MASK ; 
 int be32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xcan_write_frame(struct xcan_priv *priv, struct sk_buff *skb,
			     int frame_offset)
{
	u32 id, dlc, data[2] = {0, 0};
	struct can_frame *cf = (struct can_frame *)skb->data;

	/* Watch carefully on the bit sequence */
	if (cf->can_id & CAN_EFF_FLAG) {
		/* Extended CAN ID format */
		id = ((cf->can_id & CAN_EFF_MASK) << XCAN_IDR_ID2_SHIFT) &
			XCAN_IDR_ID2_MASK;
		id |= (((cf->can_id & CAN_EFF_MASK) >>
			(CAN_EFF_ID_BITS-CAN_SFF_ID_BITS)) <<
			XCAN_IDR_ID1_SHIFT) & XCAN_IDR_ID1_MASK;

		/* The substibute remote TX request bit should be "1"
		 * for extended frames as in the Xilinx CAN datasheet
		 */
		id |= XCAN_IDR_IDE_MASK | XCAN_IDR_SRR_MASK;

		if (cf->can_id & CAN_RTR_FLAG)
			/* Extended frames remote TX request */
			id |= XCAN_IDR_RTR_MASK;
	} else {
		/* Standard CAN ID format */
		id = ((cf->can_id & CAN_SFF_MASK) << XCAN_IDR_ID1_SHIFT) &
			XCAN_IDR_ID1_MASK;

		if (cf->can_id & CAN_RTR_FLAG)
			/* Standard frames remote TX request */
			id |= XCAN_IDR_SRR_MASK;
	}

	dlc = cf->can_dlc << XCAN_DLCR_DLC_SHIFT;

	if (cf->can_dlc > 0)
		data[0] = be32_to_cpup((__be32 *)(cf->data + 0));
	if (cf->can_dlc > 4)
		data[1] = be32_to_cpup((__be32 *)(cf->data + 4));

	priv->write_reg(priv, XCAN_FRAME_ID_OFFSET(frame_offset), id);
	/* If the CAN frame is RTR frame this write triggers transmission
	 * (not on CAN FD)
	 */
	priv->write_reg(priv, XCAN_FRAME_DLC_OFFSET(frame_offset), dlc);
	if (!(cf->can_id & CAN_RTR_FLAG)) {
		priv->write_reg(priv, XCAN_FRAME_DW1_OFFSET(frame_offset),
				data[0]);
		/* If the CAN frame is Standard/Extended frame this
		 * write triggers transmission (not on CAN FD)
		 */
		priv->write_reg(priv, XCAN_FRAME_DW2_OFFSET(frame_offset),
				data[1]);
	}
}