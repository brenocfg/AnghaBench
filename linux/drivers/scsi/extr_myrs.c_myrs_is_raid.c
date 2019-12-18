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
struct scsi_device {scalar_t__ channel; int /*<<< orphan*/  host; } ;
struct myrs_hba {TYPE_1__* ctlr_info; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ physchan_present; } ;

/* Variables and functions */
 struct myrs_hba* shost_priv (int /*<<< orphan*/ ) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static int
myrs_is_raid(struct device *dev)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	struct myrs_hba *cs = shost_priv(sdev->host);

	return (sdev->channel >= cs->ctlr_info->physchan_present) ? 1 : 0;
}