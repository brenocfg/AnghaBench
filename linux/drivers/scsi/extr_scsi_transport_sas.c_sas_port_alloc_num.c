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
struct sas_port {int dummy; } ;
struct sas_host_attrs {int /*<<< orphan*/  lock; int /*<<< orphan*/  next_port_id; } ;
struct sas_expander_device {int /*<<< orphan*/  next_port_id; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 struct sas_rphy* dev_to_rphy (struct device*) ; 
 struct Scsi_Host* dev_to_shost (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sas_expander_device* rphy_to_expander_device (struct sas_rphy*) ; 
 struct sas_port* sas_port_alloc (struct device*,int) ; 
 scalar_t__ scsi_is_sas_expander_device (struct device*) ; 
 struct sas_host_attrs* to_sas_host_attrs (struct Scsi_Host*) ; 

struct sas_port *sas_port_alloc_num(struct device *parent)
{
	int index;
	struct Scsi_Host *shost = dev_to_shost(parent);
	struct sas_host_attrs *sas_host = to_sas_host_attrs(shost);

	/* FIXME: use idr for this eventually */
	mutex_lock(&sas_host->lock);
	if (scsi_is_sas_expander_device(parent)) {
		struct sas_rphy *rphy = dev_to_rphy(parent);
		struct sas_expander_device *exp = rphy_to_expander_device(rphy);

		index = exp->next_port_id++;
	} else
		index = sas_host->next_port_id++;
	mutex_unlock(&sas_host->lock);
	return sas_port_alloc(parent, index);
}