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
typedef  int /*<<< orphan*/  u8 ;
struct vnt_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_TYPE_WRITE ; 
 int vnt_control_out (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int vnt_control_out_u8(struct vnt_private *priv, u8 reg, u8 reg_off, u8 data)
{
	return vnt_control_out(priv, MESSAGE_TYPE_WRITE,
			       reg_off, reg, sizeof(u8), &data);
}