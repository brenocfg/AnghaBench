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
struct brcmf_sdio {int /*<<< orphan*/  dcmd_resp_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int brcmf_sdio_dcmd_resp_wake(struct brcmf_sdio *bus)
{
	wake_up_interruptible(&bus->dcmd_resp_wait);

	return 0;
}