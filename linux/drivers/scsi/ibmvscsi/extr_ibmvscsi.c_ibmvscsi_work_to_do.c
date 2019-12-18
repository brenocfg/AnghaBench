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
struct ibmvscsi_host_data {TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int __ibmvscsi_work_to_do (struct ibmvscsi_host_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int ibmvscsi_work_to_do(struct ibmvscsi_host_data *hostdata)
{
	unsigned long flags;
	int rc;

	spin_lock_irqsave(hostdata->host->host_lock, flags);
	rc = __ibmvscsi_work_to_do(hostdata);
	spin_unlock_irqrestore(hostdata->host->host_lock, flags);

	return rc;
}