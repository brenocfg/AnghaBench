#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ata_timing {int /*<<< orphan*/  recover; int /*<<< orphan*/  active; } ;
struct TYPE_2__ {int /*<<< orphan*/  status_addr; int /*<<< orphan*/  device_addr; } ;
struct ata_port {TYPE_1__ ioaddr; } ;
struct ata_device {scalar_t__ class; int /*<<< orphan*/  pio_mode; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATA ; 
 int /*<<< orphan*/  ata_timing_compute (struct ata_device*,int /*<<< orphan*/ ,struct ata_timing*,int,int) ; 
 int clamp_val (int /*<<< orphan*/ ,int,int) ; 
 int inb (int) ; 
 int /*<<< orphan*/  ioread8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int) ; 

__attribute__((used)) static void ht6560b_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	u8 active, recover;
	struct ata_timing t;

	/* Get the timing data in cycles. For now play safe at 50Mhz */
	ata_timing_compute(adev, adev->pio_mode, &t, 20000, 1000);

	active = clamp_val(t.active, 2, 15);
	recover = clamp_val(t.recover, 2, 16) & 0x0F;

	inb(0x3E6);
	inb(0x3E6);
	inb(0x3E6);
	inb(0x3E6);

	iowrite8(recover << 4 | active, ap->ioaddr.device_addr);

	if (adev->class != ATA_DEV_ATA) {
		u8 rconf = inb(0x3E6);
		if (rconf & 0x24) {
			rconf &= ~0x24;
			outb(rconf, 0x3E6);
		}
	}
	ioread8(ap->ioaddr.status_addr);
}