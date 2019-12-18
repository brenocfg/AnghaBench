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
struct pp_hwmgr {struct fiji_smumgr* smu_backend; } ;
struct fiji_smumgr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct fiji_smumgr*) ; 
 struct fiji_smumgr* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ smu7_init (struct pp_hwmgr*) ; 

__attribute__((used)) static int fiji_smu_init(struct pp_hwmgr *hwmgr)
{
	struct fiji_smumgr *fiji_priv = NULL;

	fiji_priv = kzalloc(sizeof(struct fiji_smumgr), GFP_KERNEL);

	if (fiji_priv == NULL)
		return -ENOMEM;

	hwmgr->smu_backend = fiji_priv;

	if (smu7_init(hwmgr)) {
		kfree(fiji_priv);
		return -EINVAL;
	}

	return 0;
}