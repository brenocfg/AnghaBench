#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sas_internal {int dummy; } ;
struct domain_device {TYPE_4__* port; } ;
struct TYPE_8__ {TYPE_3__* ha; } ;
struct TYPE_6__ {TYPE_1__* shost; } ;
struct TYPE_7__ {TYPE_2__ core; } ;
struct TYPE_5__ {int /*<<< orphan*/  transportt; } ;

/* Variables and functions */
 struct sas_internal* to_sas_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sas_internal *dev_to_sas_internal(struct domain_device *dev)
{
	return to_sas_internal(dev->port->ha->core.shost->transportt);
}