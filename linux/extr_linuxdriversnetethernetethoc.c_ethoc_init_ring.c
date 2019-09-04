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
struct ethoc_bd {unsigned long addr; int stat; } ;
struct ethoc {int num_tx; int num_rx; void** vma; void* membase; scalar_t__ cur_rx; scalar_t__ dty_tx; scalar_t__ cur_tx; } ;

/* Variables and functions */
 scalar_t__ ETHOC_BUFSIZ ; 
 int RX_BD_EMPTY ; 
 int RX_BD_IRQ ; 
 int RX_BD_WRAP ; 
 int TX_BD_CRC ; 
 int TX_BD_IRQ ; 
 int /*<<< orphan*/  TX_BD_NUM ; 
 int TX_BD_WRAP ; 
 int /*<<< orphan*/  ethoc_write (struct ethoc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ethoc_write_bd (struct ethoc*,int,struct ethoc_bd*) ; 

__attribute__((used)) static int ethoc_init_ring(struct ethoc *dev, unsigned long mem_start)
{
	struct ethoc_bd bd;
	int i;
	void *vma;

	dev->cur_tx = 0;
	dev->dty_tx = 0;
	dev->cur_rx = 0;

	ethoc_write(dev, TX_BD_NUM, dev->num_tx);

	/* setup transmission buffers */
	bd.addr = mem_start;
	bd.stat = TX_BD_IRQ | TX_BD_CRC;
	vma = dev->membase;

	for (i = 0; i < dev->num_tx; i++) {
		if (i == dev->num_tx - 1)
			bd.stat |= TX_BD_WRAP;

		ethoc_write_bd(dev, i, &bd);
		bd.addr += ETHOC_BUFSIZ;

		dev->vma[i] = vma;
		vma += ETHOC_BUFSIZ;
	}

	bd.stat = RX_BD_EMPTY | RX_BD_IRQ;

	for (i = 0; i < dev->num_rx; i++) {
		if (i == dev->num_rx - 1)
			bd.stat |= RX_BD_WRAP;

		ethoc_write_bd(dev, dev->num_tx + i, &bd);
		bd.addr += ETHOC_BUFSIZ;

		dev->vma[dev->num_tx + i] = vma;
		vma += ETHOC_BUFSIZ;
	}

	return 0;
}