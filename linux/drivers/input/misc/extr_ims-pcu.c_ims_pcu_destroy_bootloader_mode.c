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
struct ims_pcu {int /*<<< orphan*/  async_firmware_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ims_pcu_destroy_bootloader_mode(struct ims_pcu *pcu)
{
	/* Make sure our initial firmware request has completed */
	wait_for_completion(&pcu->async_firmware_done);
}