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
typedef  int u16 ;

/* Variables and functions */
 int ADVERTISE_1000XPAUSE ; 
 int ADVERTISE_1000XPSE_ASYM ; 
 int FLOW_CTRL_RX ; 
 int FLOW_CTRL_TX ; 

__attribute__((used)) static u16 tg3_advert_flowctrl_1000X(u8 flow_ctrl)
{
	u16 miireg;

	if ((flow_ctrl & FLOW_CTRL_TX) && (flow_ctrl & FLOW_CTRL_RX))
		miireg = ADVERTISE_1000XPAUSE;
	else if (flow_ctrl & FLOW_CTRL_TX)
		miireg = ADVERTISE_1000XPSE_ASYM;
	else if (flow_ctrl & FLOW_CTRL_RX)
		miireg = ADVERTISE_1000XPAUSE | ADVERTISE_1000XPSE_ASYM;
	else
		miireg = 0;

	return miireg;
}