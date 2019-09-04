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
struct TYPE_4__ {int dma; void** cpu; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr; int /*<<< orphan*/  pci; } ;
struct bttv {TYPE_2__ main; TYPE_1__ c; } ;

/* Variables and functions */
 int BT848_FIFO_STATUS_VRE ; 
 int BT848_FIFO_STATUS_VRO ; 
 int BT848_RISC_JUMP ; 
 int BT848_RISC_RESYNC ; 
 int BT848_RISC_SYNC ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int btcx_riscmem_alloc (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,unsigned long long) ; 

int
bttv_risc_init_main(struct bttv *btv)
{
	int rc;

	if ((rc = btcx_riscmem_alloc(btv->c.pci,&btv->main,PAGE_SIZE)) < 0)
		return rc;
	dprintk("%d: risc main @ %08llx\n",
		btv->c.nr, (unsigned long long)btv->main.dma);

	btv->main.cpu[0] = cpu_to_le32(BT848_RISC_SYNC | BT848_RISC_RESYNC |
				       BT848_FIFO_STATUS_VRE);
	btv->main.cpu[1] = cpu_to_le32(0);
	btv->main.cpu[2] = cpu_to_le32(BT848_RISC_JUMP);
	btv->main.cpu[3] = cpu_to_le32(btv->main.dma + (4<<2));

	/* top field */
	btv->main.cpu[4] = cpu_to_le32(BT848_RISC_JUMP);
	btv->main.cpu[5] = cpu_to_le32(btv->main.dma + (6<<2));
	btv->main.cpu[6] = cpu_to_le32(BT848_RISC_JUMP);
	btv->main.cpu[7] = cpu_to_le32(btv->main.dma + (8<<2));

	btv->main.cpu[8] = cpu_to_le32(BT848_RISC_SYNC | BT848_RISC_RESYNC |
				       BT848_FIFO_STATUS_VRO);
	btv->main.cpu[9] = cpu_to_le32(0);

	/* bottom field */
	btv->main.cpu[10] = cpu_to_le32(BT848_RISC_JUMP);
	btv->main.cpu[11] = cpu_to_le32(btv->main.dma + (12<<2));
	btv->main.cpu[12] = cpu_to_le32(BT848_RISC_JUMP);
	btv->main.cpu[13] = cpu_to_le32(btv->main.dma + (14<<2));

	/* jump back to top field */
	btv->main.cpu[14] = cpu_to_le32(BT848_RISC_JUMP);
	btv->main.cpu[15] = cpu_to_le32(btv->main.dma + (0<<2));

	return 0;
}