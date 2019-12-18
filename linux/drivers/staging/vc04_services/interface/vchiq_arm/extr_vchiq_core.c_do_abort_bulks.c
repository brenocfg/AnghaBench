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
struct vchiq_service {int /*<<< orphan*/  bulk_rx; int /*<<< orphan*/  bulk_tx; int /*<<< orphan*/  bulk_mutex; } ;
typedef  scalar_t__ VCHIQ_STATUS_T ;

/* Variables and functions */
 scalar_t__ VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  abort_outstanding_bulks (struct vchiq_service*,int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ notify_bulks (struct vchiq_service*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_abort_bulks(struct vchiq_service *service)
{
	VCHIQ_STATUS_T status;

	/* Abort any outstanding bulk transfers */
	if (mutex_lock_killable(&service->bulk_mutex))
		return 0;
	abort_outstanding_bulks(service, &service->bulk_tx);
	abort_outstanding_bulks(service, &service->bulk_rx);
	mutex_unlock(&service->bulk_mutex);

	status = notify_bulks(service, &service->bulk_tx, 0/*!retry_poll*/);
	if (status == VCHIQ_SUCCESS)
		status = notify_bulks(service, &service->bulk_rx,
			0/*!retry_poll*/);
	return (status == VCHIQ_SUCCESS);
}