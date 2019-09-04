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
struct ubi_device {TYPE_1__* fm; int /*<<< orphan*/  fm_wl_pool; int /*<<< orphan*/  fm_pool; } ;
struct TYPE_2__ {int used_blocks; struct TYPE_2__** e; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  return_unused_pool_pebs (struct ubi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ubi_fastmap_close(struct ubi_device *ubi)
{
	int i;

	return_unused_pool_pebs(ubi, &ubi->fm_pool);
	return_unused_pool_pebs(ubi, &ubi->fm_wl_pool);

	if (ubi->fm) {
		for (i = 0; i < ubi->fm->used_blocks; i++)
			kfree(ubi->fm->e[i]);
	}
	kfree(ubi->fm);
}