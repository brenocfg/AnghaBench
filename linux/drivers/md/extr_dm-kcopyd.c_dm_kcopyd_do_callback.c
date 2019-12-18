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
struct kcopyd_job {int read_err; unsigned long write_err; struct dm_kcopyd_client* kc; } ;
struct dm_kcopyd_client {int /*<<< orphan*/  callback_jobs; } ;

/* Variables and functions */
 int /*<<< orphan*/  push (int /*<<< orphan*/ *,struct kcopyd_job*) ; 
 int /*<<< orphan*/  wake (struct dm_kcopyd_client*) ; 

void dm_kcopyd_do_callback(void *j, int read_err, unsigned long write_err)
{
	struct kcopyd_job *job = j;
	struct dm_kcopyd_client *kc = job->kc;

	job->read_err = read_err;
	job->write_err = write_err;

	push(&kc->callback_jobs, job);
	wake(kc);
}