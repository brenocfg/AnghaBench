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
struct rtnl_link_stats64 {int dummy; } ;
struct opa_vnic_stats {int dummy; } ;
struct net_device {int dummy; } ;
struct hfi1_vnic_vport_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi1_vnic_update_stats (struct hfi1_vnic_vport_info*,struct opa_vnic_stats*) ; 
 struct hfi1_vnic_vport_info* opa_vnic_dev_priv (struct net_device*) ; 

__attribute__((used)) static void hfi1_vnic_get_stats64(struct net_device *netdev,
				  struct rtnl_link_stats64 *stats)
{
	struct opa_vnic_stats *vstats = (struct opa_vnic_stats *)stats;
	struct hfi1_vnic_vport_info *vinfo = opa_vnic_dev_priv(netdev);

	hfi1_vnic_update_stats(vinfo, vstats);
}