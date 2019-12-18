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
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {scalar_t__ offset; } ;
struct TYPE_6__ {unsigned long size; scalar_t__ offset; } ;
struct TYPE_5__ {int offset; } ;
struct TYPE_8__ {int paddr; TYPE_3__ code; TYPE_2__ data; TYPE_1__ bin_data; int /*<<< orphan*/  vaddr; } ;
struct falcon {int /*<<< orphan*/  dev; TYPE_4__ firmware; scalar_t__ regs; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FALCON_BOOTVEC ; 
 scalar_t__ FALCON_CPUCTL ; 
 int FALCON_CPUCTL_STARTCPU ; 
 scalar_t__ FALCON_DMACTL ; 
 int FALCON_DMACTL_DMEM_SCRUBBING ; 
 int FALCON_DMACTL_IMEM_SCRUBBING ; 
 scalar_t__ FALCON_DMATRFBASE ; 
 scalar_t__ FALCON_IRQDEST ; 
 int FALCON_IRQDEST_EXT (int) ; 
 int FALCON_IRQDEST_EXTERR ; 
 int FALCON_IRQDEST_HALT ; 
 int FALCON_IRQDEST_SWGEN0 ; 
 int FALCON_IRQDEST_SWGEN1 ; 
 scalar_t__ FALCON_IRQMSET ; 
 int FALCON_IRQMSET_EXT (int) ; 
 int FALCON_IRQMSET_EXTERR ; 
 int FALCON_IRQMSET_HALT ; 
 int FALCON_IRQMSET_SWGEN0 ; 
 int FALCON_IRQMSET_SWGEN1 ; 
 int FALCON_IRQMSET_WDTMR ; 
 scalar_t__ FALCON_ITFEN ; 
 int FALCON_ITFEN_CTXEN ; 
 int FALCON_ITFEN_MTHDEN ; 
 int /*<<< orphan*/  FALCON_MEMORY_DATA ; 
 int /*<<< orphan*/  FALCON_MEMORY_IMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  falcon_copy_chunk (struct falcon*,scalar_t__,unsigned long,int /*<<< orphan*/ ) ; 
 int falcon_wait_idle (struct falcon*) ; 
 int /*<<< orphan*/  falcon_writel (struct falcon*,int,scalar_t__) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 

int falcon_boot(struct falcon *falcon)
{
	unsigned long offset;
	u32 value;
	int err;

	if (!falcon->firmware.vaddr)
		return -EINVAL;

	err = readl_poll_timeout(falcon->regs + FALCON_DMACTL, value,
				 (value & (FALCON_DMACTL_IMEM_SCRUBBING |
					   FALCON_DMACTL_DMEM_SCRUBBING)) == 0,
				 10, 10000);
	if (err < 0)
		return err;

	falcon_writel(falcon, 0, FALCON_DMACTL);

	/* setup the address of the binary data so Falcon can access it later */
	falcon_writel(falcon, (falcon->firmware.paddr +
			       falcon->firmware.bin_data.offset) >> 8,
		      FALCON_DMATRFBASE);

	/* copy the data segment into Falcon internal memory */
	for (offset = 0; offset < falcon->firmware.data.size; offset += 256)
		falcon_copy_chunk(falcon,
				  falcon->firmware.data.offset + offset,
				  offset, FALCON_MEMORY_DATA);

	/* copy the first code segment into Falcon internal memory */
	falcon_copy_chunk(falcon, falcon->firmware.code.offset,
			  0, FALCON_MEMORY_IMEM);

	/* setup falcon interrupts */
	falcon_writel(falcon, FALCON_IRQMSET_EXT(0xff) |
			      FALCON_IRQMSET_SWGEN1 |
			      FALCON_IRQMSET_SWGEN0 |
			      FALCON_IRQMSET_EXTERR |
			      FALCON_IRQMSET_HALT |
			      FALCON_IRQMSET_WDTMR,
		      FALCON_IRQMSET);
	falcon_writel(falcon, FALCON_IRQDEST_EXT(0xff) |
			      FALCON_IRQDEST_SWGEN1 |
			      FALCON_IRQDEST_SWGEN0 |
			      FALCON_IRQDEST_EXTERR |
			      FALCON_IRQDEST_HALT,
		      FALCON_IRQDEST);

	/* enable interface */
	falcon_writel(falcon, FALCON_ITFEN_MTHDEN |
			      FALCON_ITFEN_CTXEN,
		      FALCON_ITFEN);

	/* boot falcon */
	falcon_writel(falcon, 0x00000000, FALCON_BOOTVEC);
	falcon_writel(falcon, FALCON_CPUCTL_STARTCPU, FALCON_CPUCTL);

	err = falcon_wait_idle(falcon);
	if (err < 0) {
		dev_err(falcon->dev, "Falcon boot failed due to timeout\n");
		return err;
	}

	return 0;
}