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
struct zfcp_adapter {int adapter_features; int /*<<< orphan*/  qdio; } ;
struct fsf_statistics_info {int dummy; } ;
struct fsf_qtcb_bottom_config {struct fsf_statistics_info stat_info; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__* hostdata; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int FSF_FEATURE_MEASUREMENT_DATA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct Scsi_Host* dev_to_shost (struct device*) ; 
 int /*<<< orphan*/  kfree (struct fsf_qtcb_bottom_config*) ; 
 struct fsf_qtcb_bottom_config* kzalloc (int,int /*<<< orphan*/ ) ; 
 int zfcp_fsf_exchange_config_data_sync (int /*<<< orphan*/ ,struct fsf_qtcb_bottom_config*) ; 

__attribute__((used)) static int zfcp_sysfs_adapter_ex_config(struct device *dev,
					struct fsf_statistics_info *stat_inf)
{
	struct Scsi_Host *scsi_host = dev_to_shost(dev);
	struct fsf_qtcb_bottom_config *qtcb_config;
	struct zfcp_adapter *adapter;
	int retval;

	adapter = (struct zfcp_adapter *) scsi_host->hostdata[0];
	if (!(adapter->adapter_features & FSF_FEATURE_MEASUREMENT_DATA))
		return -EOPNOTSUPP;

	qtcb_config = kzalloc(sizeof(struct fsf_qtcb_bottom_config),
			      GFP_KERNEL);
	if (!qtcb_config)
		return -ENOMEM;

	retval = zfcp_fsf_exchange_config_data_sync(adapter->qdio, qtcb_config);
	if (!retval)
		*stat_inf = qtcb_config->stat_info;

	kfree(qtcb_config);
	return retval;
}