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
struct msb_data {int /*<<< orphan*/ * card; int /*<<< orphan*/  cache; int /*<<< orphan*/  lba_to_pba_table; int /*<<< orphan*/  used_blocks_bitmap; int /*<<< orphan*/  boot_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msb_data_clear(struct msb_data *msb)
{
	kfree(msb->boot_page);
	kfree(msb->used_blocks_bitmap);
	kfree(msb->lba_to_pba_table);
	kfree(msb->cache);
	msb->card = NULL;
}