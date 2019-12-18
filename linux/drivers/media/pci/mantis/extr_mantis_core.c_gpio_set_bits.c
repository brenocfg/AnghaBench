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
struct mantis_pci {int gpio_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_GPIF_ADDR ; 
 int /*<<< orphan*/  MANTIS_GPIF_DOUT ; 
 int mmread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void gpio_set_bits(struct mantis_pci *mantis, u32 bitpos, u8 value)
{
	u32 cur;

	cur = mmread(MANTIS_GPIF_ADDR);
	if (value)
		mantis->gpio_status = cur | (1 << bitpos);
	else
		mantis->gpio_status = cur & (~(1 << bitpos));

	mmwrite(mantis->gpio_status, MANTIS_GPIF_ADDR);
	mmwrite(0x00, MANTIS_GPIF_DOUT);
	udelay(100);
}