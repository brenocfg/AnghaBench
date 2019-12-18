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
struct TYPE_5__ {TYPE_1__* parent; } ;
struct sas_rphy {TYPE_2__ dev; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ioc; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
typedef  TYPE_3__ MPT_SCSI_HOST ;
typedef  int /*<<< orphan*/  MPT_ADAPTER ;

/* Variables and functions */
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline MPT_ADAPTER *rphy_to_ioc(struct sas_rphy *rphy)
{
	struct Scsi_Host *shost = dev_to_shost(rphy->dev.parent->parent);
	return ((MPT_SCSI_HOST *)shost->hostdata)->ioc;
}