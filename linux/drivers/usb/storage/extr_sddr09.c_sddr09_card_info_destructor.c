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
struct sddr09_card_info {int /*<<< orphan*/  pba_to_lba; int /*<<< orphan*/  lba_to_pba; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sddr09_card_info_destructor(void *extra) {
	struct sddr09_card_info *info = (struct sddr09_card_info *)extra;

	if (!info)
		return;

	kfree(info->lba_to_pba);
	kfree(info->pba_to_lba);
}