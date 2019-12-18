#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int device_type; } ;
struct device {int dummy; } ;
struct sas_rphy {scalar_t__ q; TYPE_1__ identify; struct device dev; } ;

/* Variables and functions */
#define  SAS_EDGE_EXPANDER_DEVICE 130 
#define  SAS_END_DEVICE 129 
#define  SAS_FANOUT_EXPANDER_DEVICE 128 
 int /*<<< orphan*/  bsg_unregister_queue (scalar_t__) ; 
 int /*<<< orphan*/  device_del (struct device*) ; 
 int /*<<< orphan*/  sas_remove_children (struct device*) ; 
 int /*<<< orphan*/  sas_rphy_unlink (struct sas_rphy*) ; 
 int /*<<< orphan*/  scsi_remove_target (struct device*) ; 
 int /*<<< orphan*/  transport_remove_device (struct device*) ; 

void
sas_rphy_remove(struct sas_rphy *rphy)
{
	struct device *dev = &rphy->dev;

	switch (rphy->identify.device_type) {
	case SAS_END_DEVICE:
		scsi_remove_target(dev);
		break;
	case SAS_EDGE_EXPANDER_DEVICE:
	case SAS_FANOUT_EXPANDER_DEVICE:
		sas_remove_children(dev);
		break;
	default:
		break;
	}

	sas_rphy_unlink(rphy);
	if (rphy->q)
		bsg_unregister_queue(rphy->q);
	transport_remove_device(dev);
	device_del(dev);
}