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
struct bnx2 {int /*<<< orphan*/ * rv2p_firmware; int /*<<< orphan*/ * mips_firmware; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2_release_firmware(struct bnx2 *bp)
{
	if (bp->rv2p_firmware) {
		release_firmware(bp->mips_firmware);
		release_firmware(bp->rv2p_firmware);
		bp->rv2p_firmware = NULL;
	}
}