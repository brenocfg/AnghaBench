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
struct ata_device {int max_sectors; TYPE_3__* link; } ;
struct ahci_host_priv {int flags; } ;
struct TYPE_6__ {TYPE_2__* ap; } ;
struct TYPE_5__ {TYPE_1__* host; } ;
struct TYPE_4__ {struct ahci_host_priv* private_data; } ;

/* Variables and functions */
 int AHCI_HFLAG_SECT255 ; 
 int /*<<< orphan*/  ata_dev_info (struct ata_device*,char*) ; 

__attribute__((used)) static void ahci_dev_config(struct ata_device *dev)
{
	struct ahci_host_priv *hpriv = dev->link->ap->host->private_data;

	if (hpriv->flags & AHCI_HFLAG_SECT255) {
		dev->max_sectors = 255;
		ata_dev_info(dev,
			     "SB600 AHCI: limiting to 255 sectors per cmd\n");
	}
}