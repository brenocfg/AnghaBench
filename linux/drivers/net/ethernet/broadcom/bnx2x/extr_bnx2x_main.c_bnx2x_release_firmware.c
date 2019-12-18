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
struct bnx2x {int /*<<< orphan*/ * firmware; int /*<<< orphan*/  init_data; int /*<<< orphan*/  init_ops; int /*<<< orphan*/  init_ops_offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2x_release_firmware(struct bnx2x *bp)
{
	kfree(bp->init_ops_offsets);
	kfree(bp->init_ops);
	kfree(bp->init_data);
	release_firmware(bp->firmware);
	bp->firmware = NULL;
}