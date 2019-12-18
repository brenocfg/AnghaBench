#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cx88_riscmem {int /*<<< orphan*/  dma; scalar_t__ cpu; int /*<<< orphan*/  size; } ;
struct cx88_audio_dev {TYPE_1__* buf; int /*<<< orphan*/  pci; int /*<<< orphan*/  dma_size; } ;
struct TYPE_3__ {struct cx88_riscmem risc; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cx88_alsa_dma_free (TYPE_1__*) ; 
 int /*<<< orphan*/  cx88_alsa_dma_unmap (struct cx88_audio_dev*) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsp_buffer_free(struct cx88_audio_dev *chip)
{
	struct cx88_riscmem *risc = &chip->buf->risc;

	WARN_ON(!chip->dma_size);

	dprintk(2, "Freeing buffer\n");
	cx88_alsa_dma_unmap(chip);
	cx88_alsa_dma_free(chip->buf);
	if (risc->cpu)
		pci_free_consistent(chip->pci, risc->size,
				    risc->cpu, risc->dma);
	kfree(chip->buf);

	chip->buf = NULL;

	return 0;
}