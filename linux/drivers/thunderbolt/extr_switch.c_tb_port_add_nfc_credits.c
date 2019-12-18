#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int nfc_credits; } ;
struct tb_port {TYPE_2__ config; TYPE_1__* sw; } ;
struct TYPE_3__ {scalar_t__ is_unplugged; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_PORT ; 
 int TB_PORT_NFC_CREDITS_MASK ; 
 int /*<<< orphan*/  tb_port_dbg (struct tb_port*,char*,int,int) ; 
 int tb_port_write (struct tb_port*,int*,int /*<<< orphan*/ ,int,int) ; 

int tb_port_add_nfc_credits(struct tb_port *port, int credits)
{
	u32 nfc_credits;

	if (credits == 0 || port->sw->is_unplugged)
		return 0;

	nfc_credits = port->config.nfc_credits & TB_PORT_NFC_CREDITS_MASK;
	nfc_credits += credits;

	tb_port_dbg(port, "adding %d NFC credits to %lu",
		    credits, port->config.nfc_credits & TB_PORT_NFC_CREDITS_MASK);

	port->config.nfc_credits &= ~TB_PORT_NFC_CREDITS_MASK;
	port->config.nfc_credits |= nfc_credits;

	return tb_port_write(port, &port->config.nfc_credits,
			     TB_CFG_PORT, 4, 1);
}