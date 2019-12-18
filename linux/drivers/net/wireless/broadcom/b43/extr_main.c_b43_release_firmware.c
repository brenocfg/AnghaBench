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
struct TYPE_2__ {int /*<<< orphan*/  initvals_band; int /*<<< orphan*/  initvals; int /*<<< orphan*/  pcm; int /*<<< orphan*/  ucode; } ;
struct b43_wldev {TYPE_1__ fw; int /*<<< orphan*/  fw_load_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_do_release_fw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b43_release_firmware(struct b43_wldev *dev)
{
	complete(&dev->fw_load_complete);
	b43_do_release_fw(&dev->fw.ucode);
	b43_do_release_fw(&dev->fw.pcm);
	b43_do_release_fw(&dev->fw.initvals);
	b43_do_release_fw(&dev->fw.initvals_band);
}