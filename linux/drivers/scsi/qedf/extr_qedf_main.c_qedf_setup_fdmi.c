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
typedef  int u8 ;
struct qedf_ctx {TYPE_1__* pdev; struct fc_lport* lport; } ;
struct fc_lport {int fdmi_enabled; int /*<<< orphan*/  host; } ;
struct fc_host_attrs {int /*<<< orphan*/  firmware_version; int /*<<< orphan*/  driver_version; int /*<<< orphan*/  hardware_version; int /*<<< orphan*/  model_description; int /*<<< orphan*/  model; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  serial_number; } ;
struct TYPE_3__ {int revision; } ;

/* Variables and functions */
 int FW_ENGINEERING_VERSION ; 
 int FW_MAJOR_VERSION ; 
 int FW_MINOR_VERSION ; 
 int FW_REVISION_VERSION ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_DSN ; 
 char* QEDF_VERSION ; 
 int pci_find_ext_capability (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (TYPE_1__*,int,int*) ; 
 struct fc_host_attrs* shost_to_fc_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 

__attribute__((used)) static void qedf_setup_fdmi(struct qedf_ctx *qedf)
{
	struct fc_lport *lport = qedf->lport;
	struct fc_host_attrs *fc_host = shost_to_fc_host(lport->host);
	u8 buf[8];
	int i, pos;

	/*
	 * fdmi_enabled needs to be set for libfc to execute FDMI registration.
	 */
	lport->fdmi_enabled = 1;

	/*
	 * Setup the necessary fc_host attributes to that will be used to fill
	 * in the FDMI information.
	 */

	/* Get the PCI-e Device Serial Number Capability */
	pos = pci_find_ext_capability(qedf->pdev, PCI_EXT_CAP_ID_DSN);
	if (pos) {
		pos += 4;
		for (i = 0; i < 8; i++)
			pci_read_config_byte(qedf->pdev, pos + i, &buf[i]);

		snprintf(fc_host->serial_number,
		    sizeof(fc_host->serial_number),
		    "%02X%02X%02X%02X%02X%02X%02X%02X",
		    buf[7], buf[6], buf[5], buf[4],
		    buf[3], buf[2], buf[1], buf[0]);
	} else
		snprintf(fc_host->serial_number,
		    sizeof(fc_host->serial_number), "Unknown");

	snprintf(fc_host->manufacturer,
	    sizeof(fc_host->manufacturer), "%s", "Cavium Inc.");

	snprintf(fc_host->model, sizeof(fc_host->model), "%s", "QL41000");

	snprintf(fc_host->model_description, sizeof(fc_host->model_description),
	    "%s", "QLogic FastLinQ QL41000 Series 10/25/40/50GGbE Controller"
	    "(FCoE)");

	snprintf(fc_host->hardware_version, sizeof(fc_host->hardware_version),
	    "Rev %d", qedf->pdev->revision);

	snprintf(fc_host->driver_version, sizeof(fc_host->driver_version),
	    "%s", QEDF_VERSION);

	snprintf(fc_host->firmware_version, sizeof(fc_host->firmware_version),
	    "%d.%d.%d.%d", FW_MAJOR_VERSION, FW_MINOR_VERSION,
	    FW_REVISION_VERSION, FW_ENGINEERING_VERSION);
}