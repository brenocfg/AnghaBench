#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct Scsi_Host {int host_no; unsigned int io_port; int this_id; int /*<<< orphan*/  sg_tablesize; int /*<<< orphan*/  base; scalar_t__ n_io_port; int /*<<< orphan*/  irq; scalar_t__ hostdata; } ;
struct TYPE_5__ {TYPE_3__* target; int /*<<< orphan*/  Lock; int /*<<< orphan*/  CurrentSC; TYPE_1__* pci_devid; scalar_t__ MmioLength; } ;
typedef  TYPE_2__ nsp32_hw_data ;
struct TYPE_6__ {scalar_t__ sync_flag; int period; scalar_t__ offset; } ;
struct TYPE_4__ {long driver_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 scalar_t__ ASYNC_OFFSET ; 
 int /*<<< orphan*/  CHIP_MODE ; 
 int /*<<< orphan*/  INDEX_REG ; 
 unsigned char OEM0 ; 
 unsigned char OEM1 ; 
 unsigned char OPTF ; 
 scalar_t__ SDTR_DONE ; 
 unsigned char nsp32_index_read1 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nsp32_model ; 
 int nsp32_read2 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_release_version ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int nsp32_show_info(struct seq_file *m, struct Scsi_Host *host)
{
	unsigned long     flags;
	nsp32_hw_data    *data;
	int               hostno;
	unsigned int      base;
	unsigned char     mode_reg;
	int               id, speed;
	long              model;

	hostno = host->host_no;
	data = (nsp32_hw_data *)host->hostdata;
	base = host->io_port;

	seq_puts(m, "NinjaSCSI-32 status\n\n");
	seq_printf(m, "Driver version:        %s, $Revision: 1.33 $\n", nsp32_release_version);
	seq_printf(m, "SCSI host No.:         %d\n",		hostno);
	seq_printf(m, "IRQ:                   %d\n",		host->irq);
	seq_printf(m, "IO:                    0x%lx-0x%lx\n", host->io_port, host->io_port + host->n_io_port - 1);
	seq_printf(m, "MMIO(virtual address): 0x%lx-0x%lx\n",	host->base, host->base + data->MmioLength - 1);
	seq_printf(m, "sg_tablesize:          %d\n",		host->sg_tablesize);
	seq_printf(m, "Chip revision:         0x%x\n",		(nsp32_read2(base, INDEX_REG) >> 8) & 0xff);

	mode_reg = nsp32_index_read1(base, CHIP_MODE);
	model    = data->pci_devid->driver_data;

#ifdef CONFIG_PM
	seq_printf(m, "Power Management:      %s\n",          (mode_reg & OPTF) ? "yes" : "no");
#endif
	seq_printf(m, "OEM:                   %ld, %s\n",     (mode_reg & (OEM0|OEM1)), nsp32_model[model]);

	spin_lock_irqsave(&(data->Lock), flags);
	seq_printf(m, "CurrentSC:             0x%p\n\n",      data->CurrentSC);
	spin_unlock_irqrestore(&(data->Lock), flags);


	seq_puts(m, "SDTR status\n");
	for (id = 0; id < ARRAY_SIZE(data->target); id++) {

		seq_printf(m, "id %d: ", id);

		if (id == host->this_id) {
			seq_puts(m, "----- NinjaSCSI-32 host adapter\n");
			continue;
		}

		if (data->target[id].sync_flag == SDTR_DONE) {
			if (data->target[id].period == 0            &&
			    data->target[id].offset == ASYNC_OFFSET ) {
				seq_puts(m, "async");
			} else {
				seq_puts(m, " sync");
			}
		} else {
			seq_puts(m, " none");
		}

		if (data->target[id].period != 0) {

			speed = 1000000 / (data->target[id].period * 4);

			seq_printf(m, " transfer %d.%dMB/s, offset %d",
				speed / 1000,
				speed % 1000,
				data->target[id].offset
				);
		}
		seq_putc(m, '\n');
	}
	return 0;
}