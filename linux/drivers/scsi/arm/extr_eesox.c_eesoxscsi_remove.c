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
struct expansion_card {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {scalar_t__ dma; } ;
struct TYPE_3__ {TYPE_2__ scsi; } ;
struct eesoxscsi_info {TYPE_1__ info; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 scalar_t__ NO_DMA ; 
 int /*<<< orphan*/  dev_attr_bus_term ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* ecard_get_drvdata (struct expansion_card*) ; 
 int /*<<< orphan*/  ecard_release_resources (struct expansion_card*) ; 
 int /*<<< orphan*/  ecard_set_drvdata (struct expansion_card*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fas216_release (struct Scsi_Host*) ; 
 int /*<<< orphan*/  fas216_remove (struct Scsi_Host*) ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct eesoxscsi_info*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 

__attribute__((used)) static void eesoxscsi_remove(struct expansion_card *ec)
{
	struct Scsi_Host *host = ecard_get_drvdata(ec);
	struct eesoxscsi_info *info = (struct eesoxscsi_info *)host->hostdata;

	ecard_set_drvdata(ec, NULL);
	fas216_remove(host);

	if (info->info.scsi.dma != NO_DMA)
		free_dma(info->info.scsi.dma);
	free_irq(ec->irq, info);

	device_remove_file(&ec->dev, &dev_attr_bus_term);

	fas216_release(host);
	scsi_host_put(host);
	ecard_release_resources(ec);
}