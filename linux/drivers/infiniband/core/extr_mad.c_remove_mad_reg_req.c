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
typedef  size_t u8 ;
struct ib_mad_port_private {TYPE_2__* version; } ;
struct ib_mad_mgmt_vendor_class_table {struct ib_mad_mgmt_vendor_class_table** vendor_class; int /*<<< orphan*/ * oui; struct ib_mad_mgmt_vendor_class_table** method_table; } ;
struct ib_mad_mgmt_vendor_class {struct ib_mad_mgmt_vendor_class** vendor_class; int /*<<< orphan*/ * oui; struct ib_mad_mgmt_vendor_class** method_table; } ;
struct ib_mad_mgmt_method_table {struct ib_mad_mgmt_method_table** vendor_class; int /*<<< orphan*/ * oui; struct ib_mad_mgmt_method_table** method_table; } ;
struct ib_mad_mgmt_class_table {struct ib_mad_mgmt_class_table** vendor_class; int /*<<< orphan*/ * oui; struct ib_mad_mgmt_class_table** method_table; } ;
struct ib_mad_agent_private {TYPE_3__* reg_req; TYPE_1__* qp_info; } ;
struct TYPE_6__ {size_t mgmt_class_version; int /*<<< orphan*/  oui; int /*<<< orphan*/  mgmt_class; } ;
struct TYPE_5__ {struct ib_mad_mgmt_vendor_class_table* vendor; struct ib_mad_mgmt_vendor_class_table* class; } ;
struct TYPE_4__ {struct ib_mad_port_private* port_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_class_table (struct ib_mad_mgmt_vendor_class_table*) ; 
 int /*<<< orphan*/  check_method_table (struct ib_mad_mgmt_vendor_class_table*) ; 
 int /*<<< orphan*/  check_vendor_class (struct ib_mad_mgmt_vendor_class_table*) ; 
 int /*<<< orphan*/  check_vendor_table (struct ib_mad_mgmt_vendor_class_table*) ; 
 size_t convert_mgmt_class (int /*<<< orphan*/ ) ; 
 int find_vendor_oui (struct ib_mad_mgmt_vendor_class_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_vendor_class (size_t) ; 
 int /*<<< orphan*/  kfree (struct ib_mad_mgmt_vendor_class_table*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remove_methods_mad_agent (struct ib_mad_mgmt_vendor_class_table*,struct ib_mad_agent_private*) ; 
 size_t vendor_class_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_mad_reg_req(struct ib_mad_agent_private *agent_priv)
{
	struct ib_mad_port_private *port_priv;
	struct ib_mad_mgmt_class_table *class;
	struct ib_mad_mgmt_method_table *method;
	struct ib_mad_mgmt_vendor_class_table *vendor;
	struct ib_mad_mgmt_vendor_class *vendor_class;
	int index;
	u8 mgmt_class;

	/*
	 * Was MAD registration request supplied
	 * with original registration ?
	 */
	if (!agent_priv->reg_req) {
		goto out;
	}

	port_priv = agent_priv->qp_info->port_priv;
	mgmt_class = convert_mgmt_class(agent_priv->reg_req->mgmt_class);
	class = port_priv->version[
			agent_priv->reg_req->mgmt_class_version].class;
	if (!class)
		goto vendor_check;

	method = class->method_table[mgmt_class];
	if (method) {
		/* Remove any methods for this mad agent */
		remove_methods_mad_agent(method, agent_priv);
		/* Now, check to see if there are any methods still in use */
		if (!check_method_table(method)) {
			/* If not, release management method table */
			kfree(method);
			class->method_table[mgmt_class] = NULL;
			/* Any management classes left ? */
			if (!check_class_table(class)) {
				/* If not, release management class table */
				kfree(class);
				port_priv->version[
					agent_priv->reg_req->
					mgmt_class_version].class = NULL;
			}
		}
	}

vendor_check:
	if (!is_vendor_class(mgmt_class))
		goto out;

	/* normalize mgmt_class to vendor range 2 */
	mgmt_class = vendor_class_index(agent_priv->reg_req->mgmt_class);
	vendor = port_priv->version[
			agent_priv->reg_req->mgmt_class_version].vendor;

	if (!vendor)
		goto out;

	vendor_class = vendor->vendor_class[mgmt_class];
	if (vendor_class) {
		index = find_vendor_oui(vendor_class, agent_priv->reg_req->oui);
		if (index < 0)
			goto out;
		method = vendor_class->method_table[index];
		if (method) {
			/* Remove any methods for this mad agent */
			remove_methods_mad_agent(method, agent_priv);
			/*
			 * Now, check to see if there are
			 * any methods still in use
			 */
			if (!check_method_table(method)) {
				/* If not, release management method table */
				kfree(method);
				vendor_class->method_table[index] = NULL;
				memset(vendor_class->oui[index], 0, 3);
				/* Any OUIs left ? */
				if (!check_vendor_class(vendor_class)) {
					/* If not, release vendor class table */
					kfree(vendor_class);
					vendor->vendor_class[mgmt_class] = NULL;
					/* Any other vendor classes left ? */
					if (!check_vendor_table(vendor)) {
						kfree(vendor);
						port_priv->version[
							agent_priv->reg_req->
							mgmt_class_version].
							vendor = NULL;
					}
				}
			}
		}
	}

out:
	return;
}