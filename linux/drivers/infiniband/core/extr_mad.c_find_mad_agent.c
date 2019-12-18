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
typedef  int u32 ;
struct ib_vendor_mad {int /*<<< orphan*/  oui; } ;
struct ib_mad_port_private {int /*<<< orphan*/  port_num; TYPE_2__* device; int /*<<< orphan*/  reg_lock; TYPE_1__* version; } ;
struct ib_mad_mgmt_vendor_class_table {struct ib_mad_mgmt_vendor_class** vendor_class; } ;
struct ib_mad_mgmt_vendor_class {struct ib_mad_mgmt_method_table** method_table; } ;
struct ib_mad_mgmt_method_table {struct ib_mad_agent_private** agent; } ;
struct ib_mad_mgmt_class_table {struct ib_mad_mgmt_method_table** method_table; } ;
struct ib_mad_hdr {size_t class_version; size_t method; int /*<<< orphan*/  mgmt_class; int /*<<< orphan*/  tid; } ;
struct TYPE_6__ {int /*<<< orphan*/  recv_handler; } ;
struct ib_mad_agent_private {TYPE_3__ agent; int /*<<< orphan*/  refcount; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct ib_mad_mgmt_vendor_class_table* vendor; struct ib_mad_mgmt_class_table* class; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct ib_mad_mgmt_method_table**) ; 
 size_t IB_MGMT_METHOD_RESP ; 
 size_t MAX_MGMT_VERSION ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 size_t convert_mgmt_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deref_mad_agent (struct ib_mad_agent_private*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int find_vendor_oui (struct ib_mad_mgmt_vendor_class*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_mad_clients ; 
 scalar_t__ ib_response_mad (struct ib_mad_hdr const*) ; 
 int /*<<< orphan*/  is_vendor_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 size_t vendor_class_index (int /*<<< orphan*/ ) ; 
 struct ib_mad_agent_private* xa_load (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct ib_mad_agent_private *
find_mad_agent(struct ib_mad_port_private *port_priv,
	       const struct ib_mad_hdr *mad_hdr)
{
	struct ib_mad_agent_private *mad_agent = NULL;
	unsigned long flags;

	if (ib_response_mad(mad_hdr)) {
		u32 hi_tid;

		/*
		 * Routing is based on high 32 bits of transaction ID
		 * of MAD.
		 */
		hi_tid = be64_to_cpu(mad_hdr->tid) >> 32;
		rcu_read_lock();
		mad_agent = xa_load(&ib_mad_clients, hi_tid);
		if (mad_agent && !atomic_inc_not_zero(&mad_agent->refcount))
			mad_agent = NULL;
		rcu_read_unlock();
	} else {
		struct ib_mad_mgmt_class_table *class;
		struct ib_mad_mgmt_method_table *method;
		struct ib_mad_mgmt_vendor_class_table *vendor;
		struct ib_mad_mgmt_vendor_class *vendor_class;
		const struct ib_vendor_mad *vendor_mad;
		int index;

		spin_lock_irqsave(&port_priv->reg_lock, flags);
		/*
		 * Routing is based on version, class, and method
		 * For "newer" vendor MADs, also based on OUI
		 */
		if (mad_hdr->class_version >= MAX_MGMT_VERSION)
			goto out;
		if (!is_vendor_class(mad_hdr->mgmt_class)) {
			class = port_priv->version[
					mad_hdr->class_version].class;
			if (!class)
				goto out;
			if (convert_mgmt_class(mad_hdr->mgmt_class) >=
			    ARRAY_SIZE(class->method_table))
				goto out;
			method = class->method_table[convert_mgmt_class(
							mad_hdr->mgmt_class)];
			if (method)
				mad_agent = method->agent[mad_hdr->method &
							  ~IB_MGMT_METHOD_RESP];
		} else {
			vendor = port_priv->version[
					mad_hdr->class_version].vendor;
			if (!vendor)
				goto out;
			vendor_class = vendor->vendor_class[vendor_class_index(
						mad_hdr->mgmt_class)];
			if (!vendor_class)
				goto out;
			/* Find matching OUI */
			vendor_mad = (const struct ib_vendor_mad *)mad_hdr;
			index = find_vendor_oui(vendor_class, vendor_mad->oui);
			if (index == -1)
				goto out;
			method = vendor_class->method_table[index];
			if (method) {
				mad_agent = method->agent[mad_hdr->method &
							  ~IB_MGMT_METHOD_RESP];
			}
		}
		if (mad_agent)
			atomic_inc(&mad_agent->refcount);
out:
		spin_unlock_irqrestore(&port_priv->reg_lock, flags);
	}

	if (mad_agent && !mad_agent->agent.recv_handler) {
		dev_notice(&port_priv->device->dev,
			   "No receive handler for client %p on port %d\n",
			   &mad_agent->agent, port_priv->port_num);
		deref_mad_agent(mad_agent);
		mad_agent = NULL;
	}

	return mad_agent;
}