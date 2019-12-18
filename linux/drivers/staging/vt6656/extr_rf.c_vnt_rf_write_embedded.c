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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct vnt_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 int IFREGCTL_REGW ; 
 int /*<<< orphan*/  MESSAGE_TYPE_WRITE_IFRF ; 
 int VNT_RF_REG_LEN ; 
 int /*<<< orphan*/  vnt_control_out (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

int vnt_rf_write_embedded(struct vnt_private *priv, u32 data)
{
	u8 reg_data[4];

	data |= (VNT_RF_REG_LEN << 3) | IFREGCTL_REGW;

	reg_data[0] = (u8)data;
	reg_data[1] = (u8)(data >> 8);
	reg_data[2] = (u8)(data >> 16);
	reg_data[3] = (u8)(data >> 24);

	vnt_control_out(priv, MESSAGE_TYPE_WRITE_IFRF,
			0, 0, ARRAY_SIZE(reg_data), reg_data);

	return true;
}