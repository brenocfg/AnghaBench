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
struct vnt_private {int bb_rx_conf; scalar_t__ short_slot_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_REQUEST_BBREG ; 
 int /*<<< orphan*/  vnt_control_out_u8 (struct vnt_private*,int /*<<< orphan*/ ,int,int) ; 

void vnt_set_vga_gain_offset(struct vnt_private *priv, u8 data)
{
	vnt_control_out_u8(priv, MESSAGE_REQUEST_BBREG, 0xE7, data);

	/* patch for 3253B0 Baseband with Cardbus module */
	if (priv->short_slot_time)
		priv->bb_rx_conf &= 0xdf; /* 1101 1111 */
	else
		priv->bb_rx_conf |= 0x20; /* 0010 0000 */

	vnt_control_out_u8(priv, MESSAGE_REQUEST_BBREG, 0x0a, priv->bb_rx_conf);
}