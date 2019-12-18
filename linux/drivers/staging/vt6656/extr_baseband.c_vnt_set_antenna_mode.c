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
typedef  int /*<<< orphan*/  u16 ;
struct vnt_private {int bb_rx_conf; } ;

/* Variables and functions */
#define  ANT_RXA 131 
#define  ANT_RXB 130 
#define  ANT_TXA 129 
#define  ANT_TXB 128 
 int /*<<< orphan*/  MESSAGE_TYPE_SET_ANTMD ; 
 int vnt_control_out (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int vnt_set_antenna_mode(struct vnt_private *priv, u8 antenna_mode)
{
	switch (antenna_mode) {
	case ANT_TXA:
	case ANT_TXB:
		break;
	case ANT_RXA:
		priv->bb_rx_conf &= 0xFC;
		break;
	case ANT_RXB:
		priv->bb_rx_conf &= 0xFE;
		priv->bb_rx_conf |= 0x02;
		break;
	}

	return vnt_control_out(priv, MESSAGE_TYPE_SET_ANTMD,
			       (u16)antenna_mode, 0, 0, NULL);
}