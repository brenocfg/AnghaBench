#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {scalar_t__ io_addr; } ;
typedef  TYPE_1__ ips_ha_t ;

/* Variables and functions */
 int IPS_BIT_EBM ; 
 int IPS_BIT_EI ; 
 scalar_t__ IPS_REG_HISR ; 
 scalar_t__ IPS_REG_SCPR ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int inb (scalar_t__) ; 

__attribute__((used)) static int
ips_isinit_copperhead(ips_ha_t * ha)
{
	uint8_t scpr;
	uint8_t isr;

	METHOD_TRACE("ips_isinit_copperhead", 1);

	isr = inb(ha->io_addr + IPS_REG_HISR);
	scpr = inb(ha->io_addr + IPS_REG_SCPR);

	if (((isr & IPS_BIT_EI) == 0) && ((scpr & IPS_BIT_EBM) == 0))
		return (0);
	else
		return (1);
}