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
struct Scsi_Host {scalar_t__ hostdata; } ;
struct TYPE_3__ {int /*<<< orphan*/  issue; int /*<<< orphan*/  disconnected; } ;
struct TYPE_4__ {TYPE_1__ queues; } ;
typedef  TYPE_2__ FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  queue_free (int /*<<< orphan*/ *) ; 

void fas216_release(struct Scsi_Host *host)
{
	FAS216_Info *info = (FAS216_Info *)host->hostdata;

	queue_free(&info->queues.disconnected);
	queue_free(&info->queues.issue);
}