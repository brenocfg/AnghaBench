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
typedef  int u16 ;
struct vnt_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_MACREG ; 
 int /*<<< orphan*/  MESSAGE_TYPE_WRITE ; 
 int /*<<< orphan*/  vnt_control_out (struct vnt_private*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

void vnt_mac_write_word(struct vnt_private *priv, u8 reg_ofs, u16 word)
{
	u8 data[2];

	data[0] = (u8)(word & 0xff);
	data[1] = (u8)(word >> 8);

	vnt_control_out(priv, MESSAGE_TYPE_WRITE, reg_ofs,
			MESSAGE_REQUEST_MACREG, ARRAY_SIZE(data), data);
}