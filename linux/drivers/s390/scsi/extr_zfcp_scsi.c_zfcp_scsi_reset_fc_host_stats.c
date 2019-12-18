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
struct zfcp_adapter {int stats_reset; struct fsf_qtcb_bottom_port* stats_reset_data; int /*<<< orphan*/  qdio; } ;
struct fsf_qtcb_bottom_port {int dummy; } ;
struct Scsi_Host {scalar_t__* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int jiffies ; 
 int /*<<< orphan*/  kfree (struct fsf_qtcb_bottom_port*) ; 
 struct fsf_qtcb_bottom_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int zfcp_fsf_exchange_port_data_sync (int /*<<< orphan*/ ,struct fsf_qtcb_bottom_port*) ; 

__attribute__((used)) static void zfcp_scsi_reset_fc_host_stats(struct Scsi_Host *shost)
{
	struct zfcp_adapter *adapter;
	struct fsf_qtcb_bottom_port *data;
	int ret;

	adapter = (struct zfcp_adapter *)shost->hostdata[0];
	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return;

	ret = zfcp_fsf_exchange_port_data_sync(adapter->qdio, data);
	if (ret)
		kfree(data);
	else {
		adapter->stats_reset = jiffies/HZ;
		kfree(adapter->stats_reset_data);
		adapter->stats_reset_data = data; /* finally freed in
						     adapter_release */
	}
}