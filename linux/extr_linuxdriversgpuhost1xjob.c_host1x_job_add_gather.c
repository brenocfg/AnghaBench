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
struct host1x_job_gather {unsigned int words; unsigned int offset; struct host1x_bo* bo; } ;
struct host1x_job {size_t num_gathers; struct host1x_job_gather* gathers; } ;
struct host1x_bo {int dummy; } ;

/* Variables and functions */

void host1x_job_add_gather(struct host1x_job *job, struct host1x_bo *bo,
			   unsigned int words, unsigned int offset)
{
	struct host1x_job_gather *gather = &job->gathers[job->num_gathers];

	gather->words = words;
	gather->bo = bo;
	gather->offset = offset;

	job->num_gathers++;
}