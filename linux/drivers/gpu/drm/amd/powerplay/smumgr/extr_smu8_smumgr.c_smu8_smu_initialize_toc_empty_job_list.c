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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {scalar_t__ kaddr; } ;
struct smu8_smumgr {TYPE_1__ toc_buffer; } ;
struct pp_hwmgr {struct smu8_smumgr* smu_backend; } ;
struct TOC {scalar_t__* JobList; } ;

/* Variables and functions */
 scalar_t__ IGNORE_JOB ; 
 int NUM_JOBLIST_ENTRIES ; 

__attribute__((used)) static int smu8_smu_initialize_toc_empty_job_list(struct pp_hwmgr *hwmgr)
{
	int i;
	struct smu8_smumgr *smu8_smu = hwmgr->smu_backend;
	struct TOC *toc = (struct TOC *)smu8_smu->toc_buffer.kaddr;

	for (i = 0; i < NUM_JOBLIST_ENTRIES; i++)
		toc->JobList[i] = (uint8_t)IGNORE_JOB;

	return 0;
}