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
typedef  int /*<<< orphan*/  u8 ;
struct sas_ssp_task {int /*<<< orphan*/  LUN; } ;
struct mvs_tmf_task {int dummy; } ;
struct domain_device {int tproto; } ;
typedef  int /*<<< orphan*/  ssp_task ;

/* Variables and functions */
 int SAS_PROTOCOL_SSP ; 
 int TMF_RESP_FUNC_ESUPP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int mvs_exec_internal_tmf_task (struct domain_device*,struct sas_ssp_task*,int,struct mvs_tmf_task*) ; 

__attribute__((used)) static int mvs_debug_issue_ssp_tmf(struct domain_device *dev,
				u8 *lun, struct mvs_tmf_task *tmf)
{
	struct sas_ssp_task ssp_task;
	if (!(dev->tproto & SAS_PROTOCOL_SSP))
		return TMF_RESP_FUNC_ESUPP;

	memcpy(ssp_task.LUN, lun, 8);

	return mvs_exec_internal_tmf_task(dev, &ssp_task,
				sizeof(ssp_task), tmf);
}