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
typedef  int /*<<< orphan*/  u64 ;
struct sas_port {int dummy; } ;
struct hpsa_sas_port {int /*<<< orphan*/  port_list_entry; int /*<<< orphan*/  sas_address; struct sas_port* port; struct hpsa_sas_node* parent_node; int /*<<< orphan*/  phy_list_head; } ;
struct hpsa_sas_node {int /*<<< orphan*/  port_list_head; int /*<<< orphan*/  parent_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hpsa_sas_port*) ; 
 struct hpsa_sas_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sas_port_add (struct sas_port*) ; 
 struct sas_port* sas_port_alloc_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_port_free (struct sas_port*) ; 

__attribute__((used)) static struct hpsa_sas_port
	*hpsa_alloc_sas_port(struct hpsa_sas_node *hpsa_sas_node,
				u64 sas_address)
{
	int rc;
	struct hpsa_sas_port *hpsa_sas_port;
	struct sas_port *port;

	hpsa_sas_port = kzalloc(sizeof(*hpsa_sas_port), GFP_KERNEL);
	if (!hpsa_sas_port)
		return NULL;

	INIT_LIST_HEAD(&hpsa_sas_port->phy_list_head);
	hpsa_sas_port->parent_node = hpsa_sas_node;

	port = sas_port_alloc_num(hpsa_sas_node->parent_dev);
	if (!port)
		goto free_hpsa_port;

	rc = sas_port_add(port);
	if (rc)
		goto free_sas_port;

	hpsa_sas_port->port = port;
	hpsa_sas_port->sas_address = sas_address;
	list_add_tail(&hpsa_sas_port->port_list_entry,
			&hpsa_sas_node->port_list_head);

	return hpsa_sas_port;

free_sas_port:
	sas_port_free(port);
free_hpsa_port:
	kfree(hpsa_sas_port);

	return NULL;
}