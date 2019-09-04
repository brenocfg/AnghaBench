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
struct iser_conn {int /*<<< orphan*/  state_mutex; int /*<<< orphan*/  state; int /*<<< orphan*/  release_work; scalar_t__ iscsi_conn; } ;
struct iscsi_endpoint {struct iser_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISER_CONN_DOWN ; 
 int /*<<< orphan*/  iscsi_destroy_endpoint (struct iscsi_endpoint*) ; 
 int /*<<< orphan*/  iser_conn_release (struct iser_conn*) ; 
 int /*<<< orphan*/  iser_conn_terminate (struct iser_conn*) ; 
 int /*<<< orphan*/  iser_info (char*,struct iscsi_endpoint*,struct iser_conn*) ; 
 int /*<<< orphan*/  iser_release_work ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_wq ; 

__attribute__((used)) static void
iscsi_iser_ep_disconnect(struct iscsi_endpoint *ep)
{
	struct iser_conn *iser_conn = ep->dd_data;

	iser_info("ep %p iser conn %p\n", ep, iser_conn);

	mutex_lock(&iser_conn->state_mutex);
	iser_conn_terminate(iser_conn);

	/*
	 * if iser_conn and iscsi_conn are bound, we must wait for
	 * iscsi_conn_stop and flush errors completion before freeing
	 * the iser resources. Otherwise we are safe to free resources
	 * immediately.
	 */
	if (iser_conn->iscsi_conn) {
		INIT_WORK(&iser_conn->release_work, iser_release_work);
		queue_work(release_wq, &iser_conn->release_work);
		mutex_unlock(&iser_conn->state_mutex);
	} else {
		iser_conn->state = ISER_CONN_DOWN;
		mutex_unlock(&iser_conn->state_mutex);
		iser_conn_release(iser_conn);
	}

	iscsi_destroy_endpoint(ep);
}