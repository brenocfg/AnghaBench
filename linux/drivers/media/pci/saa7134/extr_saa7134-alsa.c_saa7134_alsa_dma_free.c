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
struct saa7134_dmasound {int /*<<< orphan*/ * vaddr; int /*<<< orphan*/ * sglist; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int saa7134_alsa_dma_free(struct saa7134_dmasound *dma)
{
	vfree(dma->sglist);
	dma->sglist = NULL;
	vfree(dma->vaddr);
	dma->vaddr = NULL;
	return 0;
}