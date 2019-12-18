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
struct ba_lun_info {struct ba_lun_info* lun_alloc_map; struct ba_lun_info* aun_clone_map; } ;
struct ba_lun {struct ba_lun_info* ba_lun_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ba_lun_info*) ; 

void cxlflash_ba_terminate(struct ba_lun *ba_lun)
{
	struct ba_lun_info *bali = ba_lun->ba_lun_handle;

	if (bali) {
		kfree(bali->aun_clone_map);
		kfree(bali->lun_alloc_map);
		kfree(bali);
		ba_lun->ba_lun_handle = NULL;
	}
}