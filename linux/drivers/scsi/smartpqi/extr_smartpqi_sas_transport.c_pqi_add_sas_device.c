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
struct sas_rphy {int dummy; } ;
struct pqi_scsi_dev {struct pqi_sas_port* sas_port; int /*<<< orphan*/  sas_address; } ;
struct pqi_sas_port {struct sas_rphy* rphy; } ;
struct pqi_sas_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 struct pqi_sas_port* pqi_alloc_sas_port (struct pqi_sas_node*,int /*<<< orphan*/ ,struct pqi_scsi_dev*) ; 
 int /*<<< orphan*/  pqi_free_sas_port (struct pqi_sas_port*) ; 
 int pqi_sas_port_add_rphy (struct pqi_sas_port*,struct sas_rphy*) ; 
 struct sas_rphy* pqi_sas_rphy_alloc (struct pqi_sas_port*) ; 

int pqi_add_sas_device(struct pqi_sas_node *pqi_sas_node,
	struct pqi_scsi_dev *device)
{
	int rc;
	struct pqi_sas_port *pqi_sas_port;
	struct sas_rphy *rphy;

	pqi_sas_port = pqi_alloc_sas_port(pqi_sas_node,
		device->sas_address, device);
	if (!pqi_sas_port)
		return -ENOMEM;

	rphy = pqi_sas_rphy_alloc(pqi_sas_port);
	if (!rphy) {
		rc = -ENODEV;
		goto free_sas_port;
	}

	pqi_sas_port->rphy = rphy;
	device->sas_port = pqi_sas_port;

	rc = pqi_sas_port_add_rphy(pqi_sas_port, rphy);
	if (rc)
		goto free_sas_port;

	return 0;

free_sas_port:
	pqi_free_sas_port(pqi_sas_port);
	device->sas_port = NULL;

	return rc;
}