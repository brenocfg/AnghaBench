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
struct pp_hwmgr {struct iceland_smumgr* smu_backend; } ;
struct iceland_smumgr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct iceland_smumgr*) ; 
 struct iceland_smumgr* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ smu7_init (struct pp_hwmgr*) ; 

__attribute__((used)) static int iceland_smu_init(struct pp_hwmgr *hwmgr)
{
	struct iceland_smumgr *iceland_priv = NULL;

	iceland_priv = kzalloc(sizeof(struct iceland_smumgr), GFP_KERNEL);

	if (iceland_priv == NULL)
		return -ENOMEM;

	hwmgr->smu_backend = iceland_priv;

	if (smu7_init(hwmgr)) {
		kfree(iceland_priv);
		return -EINVAL;
	}

	return 0;
}