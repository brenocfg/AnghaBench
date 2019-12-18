#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct Scsi_Host* shost; } ;
struct TYPE_4__ {TYPE_1__ core; } ;
struct isci_host {TYPE_2__ sas_ha; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct Scsi_Host *to_shost(struct isci_host *ihost)
{
	return ihost->sas_ha.core.shost;
}