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
struct transport_container {int dummy; } ;
struct srp_host_attrs {int /*<<< orphan*/  next_port_id; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* dev_to_shost (struct device*) ; 
 struct srp_host_attrs* to_srp_host_attrs (struct Scsi_Host*) ; 

__attribute__((used)) static int srp_host_setup(struct transport_container *tc, struct device *dev,
			  struct device *cdev)
{
	struct Scsi_Host *shost = dev_to_shost(dev);
	struct srp_host_attrs *srp_host = to_srp_host_attrs(shost);

	atomic_set(&srp_host->next_port_id, 0);
	return 0;
}