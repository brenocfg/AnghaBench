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
struct ef4_nic {int link_advertising; int wanted_fc; } ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 int EF4_FC_RX ; 
 int EF4_FC_TX ; 

void ef4_link_set_advertising(struct ef4_nic *efx, u32 advertising)
{
	efx->link_advertising = advertising;
	if (advertising) {
		if (advertising & ADVERTISED_Pause)
			efx->wanted_fc |= (EF4_FC_TX | EF4_FC_RX);
		else
			efx->wanted_fc &= ~(EF4_FC_TX | EF4_FC_RX);
		if (advertising & ADVERTISED_Asym_Pause)
			efx->wanted_fc ^= EF4_FC_TX;
	}
}