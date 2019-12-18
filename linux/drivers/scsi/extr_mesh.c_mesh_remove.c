#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mesh_state {int /*<<< orphan*/  dma_cmd_bus; int /*<<< orphan*/  dma_cmd_space; int /*<<< orphan*/  dma_cmd_size; int /*<<< orphan*/  dma; int /*<<< orphan*/  mesh; int /*<<< orphan*/  meshintr; struct Scsi_Host* host; } ;
struct macio_dev {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mesh_state*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 scalar_t__ macio_get_drvdata (struct macio_dev*) ; 
 TYPE_1__* macio_get_pci_dev (struct macio_dev*) ; 
 int /*<<< orphan*/  macio_release_resources (struct macio_dev*) ; 
 int /*<<< orphan*/  mesh_shutdown (struct macio_dev*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  set_mesh_power (struct mesh_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mesh_remove(struct macio_dev *mdev)
{
	struct mesh_state *ms = (struct mesh_state *)macio_get_drvdata(mdev);
	struct Scsi_Host *mesh_host = ms->host;

	scsi_remove_host(mesh_host);

	free_irq(ms->meshintr, ms);

	/* Reset scsi bus */
	mesh_shutdown(mdev);

	/* Shut down chip & termination */
	set_mesh_power(ms, 0);

	/* Unmap registers & dma controller */
	iounmap(ms->mesh);
       	iounmap(ms->dma);

	/* Free DMA commands memory */
	dma_free_coherent(&macio_get_pci_dev(mdev)->dev, ms->dma_cmd_size,
			    ms->dma_cmd_space, ms->dma_cmd_bus);

	/* Release memory resources */
	macio_release_resources(mdev);

	scsi_host_put(mesh_host);

	return 0;
}