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
struct pp_hwmgr {struct polaris10_smumgr* smu_backend; } ;
struct polaris10_smumgr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct polaris10_smumgr*) ; 
 struct polaris10_smumgr* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ smu7_init (struct pp_hwmgr*) ; 

__attribute__((used)) static int polaris10_smu_init(struct pp_hwmgr *hwmgr)
{
	struct polaris10_smumgr *smu_data;

	smu_data = kzalloc(sizeof(struct polaris10_smumgr), GFP_KERNEL);
	if (smu_data == NULL)
		return -ENOMEM;

	hwmgr->smu_backend = smu_data;

	if (smu7_init(hwmgr)) {
		kfree(smu_data);
		return -EINVAL;
	}

	return 0;
}