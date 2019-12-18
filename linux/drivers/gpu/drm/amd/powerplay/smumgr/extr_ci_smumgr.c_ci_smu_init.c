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
struct pp_hwmgr {struct ci_smumgr* smu_backend; } ;
struct ci_smumgr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ci_smumgr* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_smu_init(struct pp_hwmgr *hwmgr)
{
	struct ci_smumgr *ci_priv = NULL;

	ci_priv = kzalloc(sizeof(struct ci_smumgr), GFP_KERNEL);

	if (ci_priv == NULL)
		return -ENOMEM;

	hwmgr->smu_backend = ci_priv;

	return 0;
}