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
struct fdp1_job {int dummy; } ;
struct fdp1_dev {int /*<<< orphan*/  free_job_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_job (struct fdp1_dev*,int /*<<< orphan*/ *,struct fdp1_job*) ; 
 int /*<<< orphan*/  memset (struct fdp1_job*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fdp1_job_free(struct fdp1_dev *fdp1, struct fdp1_job *job)
{
	/* Ensure that all residue from previous jobs is gone */
	memset(job, 0, sizeof(struct fdp1_job));

	list_add_job(fdp1, &fdp1->free_job_list, job);
}