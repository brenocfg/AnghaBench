#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {scalar_t__ (* init ) (TYPE_2__*) ;} ;
struct TYPE_7__ {TYPE_1__ func; TYPE_4__* pcidev; scalar_t__ mem_ptr; int /*<<< orphan*/  mem_addr; int /*<<< orphan*/  host_num; } ;
typedef  TYPE_2__ ips_ha_t ;
struct TYPE_8__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_VAR (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IPS_ONE_SEC ; 
 scalar_t__ IPS_REG_I960_IDR ; 
 int /*<<< orphan*/  MDELAY (int) ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  ips_name ; 
 int /*<<< orphan*/  pci_read_config_byte (TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int
ips_reset_morpheus(ips_ha_t * ha)
{
	int reset_counter;
	uint8_t junk;

	METHOD_TRACE("ips_reset_morpheus", 1);

	DEBUG_VAR(1, "(%s%d) ips_reset_morpheus: mem addr: %x, irq: %d",
		  ips_name, ha->host_num, ha->mem_addr, ha->pcidev->irq);

	reset_counter = 0;

	while (reset_counter < 2) {
		reset_counter++;

		writel(0x80000000, ha->mem_ptr + IPS_REG_I960_IDR);

		/* Delay for 5 Seconds */
		MDELAY(5 * IPS_ONE_SEC);

		/* Do a PCI config read to wait for adapter */
		pci_read_config_byte(ha->pcidev, 4, &junk);

		if ((*ha->func.init) (ha))
			break;
		else if (reset_counter >= 2) {

			return (0);
		}
	}

	return (1);
}