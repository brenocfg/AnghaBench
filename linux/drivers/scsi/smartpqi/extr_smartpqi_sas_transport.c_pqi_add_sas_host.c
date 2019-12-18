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
struct pqi_sas_port {int dummy; } ;
struct pqi_sas_phy {int dummy; } ;
struct pqi_sas_node {int dummy; } ;
struct pqi_ctrl_info {struct pqi_sas_node* sas_host; int /*<<< orphan*/  sas_address; } ;
struct device {int dummy; } ;
struct Scsi_Host {struct device shost_dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 struct pqi_sas_node* pqi_alloc_sas_node (struct device*) ; 
 struct pqi_sas_phy* pqi_alloc_sas_phy (struct pqi_sas_port*) ; 
 struct pqi_sas_port* pqi_alloc_sas_port (struct pqi_sas_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqi_free_sas_node (struct pqi_sas_node*) ; 
 int /*<<< orphan*/  pqi_free_sas_phy (struct pqi_sas_phy*) ; 
 int /*<<< orphan*/  pqi_free_sas_port (struct pqi_sas_port*) ; 
 int pqi_sas_port_add_phy (struct pqi_sas_phy*) ; 

int pqi_add_sas_host(struct Scsi_Host *shost, struct pqi_ctrl_info *ctrl_info)
{
	int rc;
	struct device *parent_dev;
	struct pqi_sas_node *pqi_sas_node;
	struct pqi_sas_port *pqi_sas_port;
	struct pqi_sas_phy *pqi_sas_phy;

	parent_dev = &shost->shost_dev;

	pqi_sas_node = pqi_alloc_sas_node(parent_dev);
	if (!pqi_sas_node)
		return -ENOMEM;

	pqi_sas_port = pqi_alloc_sas_port(pqi_sas_node,
		ctrl_info->sas_address, NULL);
	if (!pqi_sas_port) {
		rc = -ENODEV;
		goto free_sas_node;
	}

	pqi_sas_phy = pqi_alloc_sas_phy(pqi_sas_port);
	if (!pqi_sas_phy) {
		rc = -ENODEV;
		goto free_sas_port;
	}

	rc = pqi_sas_port_add_phy(pqi_sas_phy);
	if (rc)
		goto free_sas_phy;

	ctrl_info->sas_host = pqi_sas_node;

	return 0;

free_sas_phy:
	pqi_free_sas_phy(pqi_sas_phy);
free_sas_port:
	pqi_free_sas_port(pqi_sas_port);
free_sas_node:
	pqi_free_sas_node(pqi_sas_node);

	return rc;
}