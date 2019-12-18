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
struct tonga_smumgr {int dummy; } ;
struct pp_hwmgr {struct tonga_smumgr* smu_backend; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct tonga_smumgr*) ; 
 struct tonga_smumgr* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ smu7_init (struct pp_hwmgr*) ; 

__attribute__((used)) static int tonga_smu_init(struct pp_hwmgr *hwmgr)
{
	struct tonga_smumgr *tonga_priv = NULL;

	tonga_priv = kzalloc(sizeof(struct tonga_smumgr), GFP_KERNEL);
	if (tonga_priv == NULL)
		return -ENOMEM;

	hwmgr->smu_backend = tonga_priv;

	if (smu7_init(hwmgr)) {
		kfree(tonga_priv);
		return -EINVAL;
	}

	return 0;
}