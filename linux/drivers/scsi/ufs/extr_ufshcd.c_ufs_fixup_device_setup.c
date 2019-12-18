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
struct ufs_hba {int dev_quirks; } ;
struct TYPE_2__ {scalar_t__ wmanufacturerid; int /*<<< orphan*/  model; } ;
struct ufs_dev_fix {int quirk; TYPE_1__ card; } ;
struct ufs_dev_desc {scalar_t__ wmanufacturerid; scalar_t__ model; } ;

/* Variables and functions */
 scalar_t__ STR_PRFX_EQUAL (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  UFS_ANY_MODEL ; 
 scalar_t__ UFS_ANY_VENDOR ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ufs_dev_fix* ufs_fixups ; 

__attribute__((used)) static void ufs_fixup_device_setup(struct ufs_hba *hba,
				   struct ufs_dev_desc *dev_desc)
{
	struct ufs_dev_fix *f;

	for (f = ufs_fixups; f->quirk; f++) {
		if ((f->card.wmanufacturerid == dev_desc->wmanufacturerid ||
		     f->card.wmanufacturerid == UFS_ANY_VENDOR) &&
		     ((dev_desc->model &&
		       STR_PRFX_EQUAL(f->card.model, dev_desc->model)) ||
		      !strcmp(f->card.model, UFS_ANY_MODEL)))
			hba->dev_quirks |= f->quirk;
	}
}