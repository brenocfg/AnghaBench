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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EnCFG_BarkerPream ; 
 int /*<<< orphan*/  MAC_REG_ENCFG2 ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_MACREG ; 
 int /*<<< orphan*/  MESSAGE_TYPE_WRITE_MASK ; 
 int /*<<< orphan*/  vnt_control_out (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void vnt_mac_enable_barker_preamble_mode(struct vnt_private *priv)
{
	u8 data[2];

	data[0] = EnCFG_BarkerPream;
	data[1] = EnCFG_BarkerPream;

	vnt_control_out(priv, MESSAGE_TYPE_WRITE_MASK, MAC_REG_ENCFG2,
			MESSAGE_REQUEST_MACREG, ARRAY_SIZE(data), data);
}