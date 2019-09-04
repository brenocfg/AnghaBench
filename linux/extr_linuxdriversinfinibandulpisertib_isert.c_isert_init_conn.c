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
struct isert_conn {int /*<<< orphan*/  release_work; int /*<<< orphan*/  mutex; int /*<<< orphan*/  kref; int /*<<< orphan*/  rem_wait; int /*<<< orphan*/  login_req_comp; int /*<<< orphan*/  login_comp; int /*<<< orphan*/  node; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISER_CONN_INIT ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isert_release_work ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isert_init_conn(struct isert_conn *isert_conn)
{
	isert_conn->state = ISER_CONN_INIT;
	INIT_LIST_HEAD(&isert_conn->node);
	init_completion(&isert_conn->login_comp);
	init_completion(&isert_conn->login_req_comp);
	init_waitqueue_head(&isert_conn->rem_wait);
	kref_init(&isert_conn->kref);
	mutex_init(&isert_conn->mutex);
	INIT_WORK(&isert_conn->release_work, isert_release_work);
}