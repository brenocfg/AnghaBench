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
struct pata_icside_state {TYPE_2__* port; } ;
struct ata_timing {int active; int recover; int cycle; } ;
struct ata_port {size_t port_no; TYPE_1__* host; } ;
struct ata_device {size_t devno; int /*<<< orphan*/  dma_mode; } ;
struct TYPE_4__ {unsigned int* speed; } ;
struct TYPE_3__ {struct pata_icside_state* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_dev_info (struct ata_device*,char*,int,int,int,char) ; 
 scalar_t__ ata_timing_compute (struct ata_device*,int /*<<< orphan*/ ,struct ata_timing*,int,int) ; 

__attribute__((used)) static void pata_icside_set_dmamode(struct ata_port *ap, struct ata_device *adev)
{
	struct pata_icside_state *state = ap->host->private_data;
	struct ata_timing t;
	unsigned int cycle;
	char iomd_type;

	/*
	 * DMA is based on a 16MHz clock
	 */
	if (ata_timing_compute(adev, adev->dma_mode, &t, 1000, 1))
		return;

	/*
	 * Choose the IOMD cycle timing which ensure that the interface
	 * satisfies the measured active, recovery and cycle times.
	 */
	if (t.active <= 50 && t.recover <= 375 && t.cycle <= 425)
		iomd_type = 'D', cycle = 187;
	else if (t.active <= 125 && t.recover <= 375 && t.cycle <= 500)
		iomd_type = 'C', cycle = 250;
	else if (t.active <= 200 && t.recover <= 550 && t.cycle <= 750)
		iomd_type = 'B', cycle = 437;
	else
		iomd_type = 'A', cycle = 562;

	ata_dev_info(adev, "timings: act %dns rec %dns cyc %dns (%c)\n",
		     t.active, t.recover, t.cycle, iomd_type);

	state->port[ap->port_no].speed[adev->devno] = cycle;
}