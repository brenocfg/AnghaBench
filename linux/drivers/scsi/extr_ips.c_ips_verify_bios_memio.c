#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {scalar_t__ mem_ptr; TYPE_1__* pcidev; } ;
typedef  TYPE_2__ ips_ha_t ;
struct TYPE_4__ {scalar_t__ revision; } ;

/* Variables and functions */
 scalar_t__ IPS_REG_FLAP ; 
 scalar_t__ IPS_REG_FLDP ; 
 scalar_t__ IPS_REVID_TROMBONE64 ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int
ips_verify_bios_memio(ips_ha_t * ha, char *buffer, uint32_t buffersize,
		      uint32_t offset)
{
	uint8_t checksum;
	int i;

	METHOD_TRACE("ips_verify_bios_memio", 1);

	/* test 1st byte */
	writel(0, ha->mem_ptr + IPS_REG_FLAP);
	if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	if (readb(ha->mem_ptr + IPS_REG_FLDP) != 0x55)
		return (1);

	writel(1, ha->mem_ptr + IPS_REG_FLAP);
	if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */
	if (readb(ha->mem_ptr + IPS_REG_FLDP) != 0xAA)
		return (1);

	checksum = 0xff;
	for (i = 2; i < buffersize; i++) {

		writel(i + offset, ha->mem_ptr + IPS_REG_FLAP);
		if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
			udelay(25);	/* 25 us */

		checksum =
		    (uint8_t) checksum + readb(ha->mem_ptr + IPS_REG_FLDP);
	}

	if (checksum != 0)
		/* failure */
		return (1);
	else
		/* success */
		return (0);
}