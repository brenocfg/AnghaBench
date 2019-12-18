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
struct ibmvscsi_host_data {int /*<<< orphan*/  dev; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ibmvscsi_reset_host (struct ibmvscsi_host_data*) ; 
 struct ibmvscsi_host_data* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int ibmvscsi_host_reset(struct Scsi_Host *shost, int reset_type)
{
	struct ibmvscsi_host_data *hostdata = shost_priv(shost);

	dev_info(hostdata->dev, "Initiating adapter reset!\n");
	ibmvscsi_reset_host(hostdata);

	return 0;
}