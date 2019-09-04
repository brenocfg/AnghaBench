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
struct pata_icside_state {scalar_t__ dma; } ;
struct expansion_card {int dummy; } ;
struct ata_host {struct pata_icside_state* private_data; } ;

/* Variables and functions */
 scalar_t__ NO_DMA ; 
 int /*<<< orphan*/  ata_host_detach (struct ata_host*) ; 
 struct ata_host* ecard_get_drvdata (struct expansion_card*) ; 
 int /*<<< orphan*/  ecard_release_resources (struct expansion_card*) ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  pata_icside_shutdown (struct expansion_card*) ; 

__attribute__((used)) static void pata_icside_remove(struct expansion_card *ec)
{
	struct ata_host *host = ecard_get_drvdata(ec);
	struct pata_icside_state *state = host->private_data;

	ata_host_detach(host);

	pata_icside_shutdown(ec);

	/*
	 * don't NULL out the drvdata - devres/libata wants it
	 * to free the ata_host structure.
	 */
	if (state->dma != NO_DMA)
		free_dma(state->dma);

	ecard_release_resources(ec);
}