#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct ide_timing {int recover; int active; int setup; } ;
struct TYPE_7__ {scalar_t__ channel; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_8__ {size_t dn; int pio_mode; int dma_mode; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
#define  ARTTIM0 134 
#define  ARTTIM1 133 
#define  ARTTIM23 132 
 int ARTTIM23_INTR_CH1 ; 
#define  DRWTIM0 131 
#define  DRWTIM1 130 
#define  DRWTIM2 129 
#define  DRWTIM3 128 
 int /*<<< orphan*/  IDE_TIMING_SETUP ; 
 TYPE_2__* ide_get_pair_dev (TYPE_2__*) ; 
 int ide_pci_clk ; 
 int /*<<< orphan*/  ide_timing_compute (TYPE_2__*,int,struct ide_timing*,unsigned long const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_timing_merge (struct ide_timing*,struct ide_timing*,struct ide_timing*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int const,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int const,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmd64x_program_timings(ide_drive_t *drive, u8 mode)
{
	ide_hwif_t *hwif = drive->hwif;
	struct pci_dev *dev = to_pci_dev(drive->hwif->dev);
	int bus_speed = ide_pci_clk ? ide_pci_clk : 33;
	const unsigned long T = 1000000 / bus_speed;
	static const u8 recovery_values[] =
		{15, 15, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0};
	static const u8 setup_values[] = {0x40, 0x40, 0x40, 0x80, 0, 0xc0};
	static const u8 arttim_regs[4] = {ARTTIM0, ARTTIM1, ARTTIM23, ARTTIM23};
	static const u8 drwtim_regs[4] = {DRWTIM0, DRWTIM1, DRWTIM2, DRWTIM3};
	struct ide_timing t;
	u8 arttim = 0;

	ide_timing_compute(drive, mode, &t, T, 0);

	/*
	 * In case we've got too long recovery phase, try to lengthen
	 * the active phase
	 */
	if (t.recover > 16) {
		t.active += t.recover - 16;
		t.recover = 16;
	}
	if (t.active > 16)		/* shouldn't actually happen... */
		t.active = 16;

	/*
	 * Convert values to internal chipset representation
	 */
	t.recover = recovery_values[t.recover];
	t.active &= 0x0f;

	/* Program the active/recovery counts into the DRWTIM register */
	pci_write_config_byte(dev, drwtim_regs[drive->dn],
			      (t.active << 4) | t.recover);

	/*
	 * The primary channel has individual address setup timing registers
	 * for each drive and the hardware selects the slowest timing itself.
	 * The secondary channel has one common register and we have to select
	 * the slowest address setup timing ourselves.
	 */
	if (hwif->channel) {
		ide_drive_t *pair = ide_get_pair_dev(drive);

		if (pair) {
			struct ide_timing tp;

			ide_timing_compute(pair, pair->pio_mode, &tp, T, 0);
			ide_timing_merge(&t, &tp, &t, IDE_TIMING_SETUP);
			if (pair->dma_mode) {
				ide_timing_compute(pair, pair->dma_mode,
						&tp, T, 0);
				ide_timing_merge(&tp, &t, &t, IDE_TIMING_SETUP);
			}
		}
	}

	if (t.setup > 5)		/* shouldn't actually happen... */
		t.setup = 5;

	/*
	 * Program the address setup clocks into the ARTTIM registers.
	 * Avoid clearing the secondary channel's interrupt bit.
	 */
	(void) pci_read_config_byte (dev, arttim_regs[drive->dn], &arttim);
	if (hwif->channel)
		arttim &= ~ARTTIM23_INTR_CH1;
	arttim &= ~0xc0;
	arttim |= setup_values[t.setup];
	(void) pci_write_config_byte(dev, arttim_regs[drive->dn], arttim);
}