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
struct vegam_smumgr {int dummy; } ;
struct pp_hwmgr {struct vegam_smumgr* smu_backend; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct vegam_smumgr*) ; 
 struct vegam_smumgr* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ smu7_init (struct pp_hwmgr*) ; 

__attribute__((used)) static int vegam_smu_init(struct pp_hwmgr *hwmgr)
{
	struct vegam_smumgr *smu_data;

	smu_data = kzalloc(sizeof(struct vegam_smumgr), GFP_KERNEL);
	if (smu_data == NULL)
		return -ENOMEM;

	hwmgr->smu_backend = smu_data;

	if (smu7_init(hwmgr)) {
		kfree(smu_data);
		return -EINVAL;
	}

	return 0;
}