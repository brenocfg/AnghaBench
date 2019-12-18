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
struct TYPE_2__ {int /*<<< orphan*/ * fw_hdr; int /*<<< orphan*/ * fw_bin; } ;
struct brcms_info {TYPE_1__ fw; } ;

/* Variables and functions */
 int MAX_FW_IMAGES ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcms_release_fw(struct brcms_info *wl)
{
	int i;
	for (i = 0; i < MAX_FW_IMAGES; i++) {
		release_firmware(wl->fw.fw_bin[i]);
		release_firmware(wl->fw.fw_hdr[i]);
	}
}