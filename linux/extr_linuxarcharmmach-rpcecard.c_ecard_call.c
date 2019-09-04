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
struct ecard_request {int /*<<< orphan*/ * complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  completion ; 
 int /*<<< orphan*/  ecard_mutex ; 
 struct ecard_request* ecard_req ; 
 int /*<<< orphan*/  ecard_wait ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ecard_call(struct ecard_request *req)
{
	DECLARE_COMPLETION_ONSTACK(completion);

	req->complete = &completion;

	mutex_lock(&ecard_mutex);
	ecard_req = req;
	wake_up(&ecard_wait);

	/*
	 * Now wait for kecardd to run.
	 */
	wait_for_completion(&completion);
	mutex_unlock(&ecard_mutex);
}