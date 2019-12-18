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
struct mantis_pci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_DMA_CTL ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int mantis_alloc_buffers (struct mantis_pci*) ; 
 int /*<<< orphan*/  mmwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mantis_dma_init(struct mantis_pci *mantis)
{
	int err;

	dprintk(MANTIS_DEBUG, 1, "Mantis DMA init");
	err = mantis_alloc_buffers(mantis);
	if (err < 0) {
		dprintk(MANTIS_ERROR, 1, "Error allocating DMA buffer");

		/* Stop RISC Engine */
		mmwrite(0, MANTIS_DMA_CTL);

		return err;
	}

	return 0;
}