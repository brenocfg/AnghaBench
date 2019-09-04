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
struct ata_port {TYPE_1__* host; } ;
struct ahci_host_priv {int (* stop_engine ) (struct ata_port*) ;} ;
struct TYPE_2__ {struct ahci_host_priv* private_data; } ;

/* Variables and functions */
 int ahci_stop_fis_rx (struct ata_port*) ; 
 int stub1 (struct ata_port*) ; 

__attribute__((used)) static int ahci_deinit_port(struct ata_port *ap, const char **emsg)
{
	int rc;
	struct ahci_host_priv *hpriv = ap->host->private_data;

	/* disable DMA */
	rc = hpriv->stop_engine(ap);
	if (rc) {
		*emsg = "failed to stop engine";
		return rc;
	}

	/* disable FIS reception */
	rc = ahci_stop_fis_rx(ap);
	if (rc) {
		*emsg = "failed stop FIS RX";
		return rc;
	}

	return 0;
}