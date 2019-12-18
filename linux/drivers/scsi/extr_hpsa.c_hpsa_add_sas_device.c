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
struct hpsa_scsi_dev_t {struct hpsa_sas_port* sas_port; int /*<<< orphan*/  sas_address; } ;
struct hpsa_sas_port {struct sas_rphy* rphy; int /*<<< orphan*/  port; } ;
struct hpsa_sas_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 struct hpsa_sas_port* hpsa_alloc_sas_port (struct hpsa_sas_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsa_free_sas_port (struct hpsa_sas_port*) ; 
 int hpsa_sas_port_add_rphy (struct hpsa_sas_port*,struct sas_rphy*) ; 
 struct sas_rphy* sas_end_device_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpsa_add_sas_device(struct hpsa_sas_node *hpsa_sas_node,
				struct hpsa_scsi_dev_t *device)
{
	int rc;
	struct hpsa_sas_port *hpsa_sas_port;
	struct sas_rphy *rphy;

	hpsa_sas_port = hpsa_alloc_sas_port(hpsa_sas_node, device->sas_address);
	if (!hpsa_sas_port)
		return -ENOMEM;

	rphy = sas_end_device_alloc(hpsa_sas_port->port);
	if (!rphy) {
		rc = -ENODEV;
		goto free_sas_port;
	}

	hpsa_sas_port->rphy = rphy;
	device->sas_port = hpsa_sas_port;

	rc = hpsa_sas_port_add_rphy(hpsa_sas_port, rphy);
	if (rc)
		goto free_sas_port;

	return 0;

free_sas_port:
	hpsa_free_sas_port(hpsa_sas_port);
	device->sas_port = NULL;

	return rc;
}