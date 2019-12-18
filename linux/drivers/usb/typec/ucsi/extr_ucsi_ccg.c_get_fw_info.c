#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ucsi_ccg {int fw_version; int /*<<< orphan*/  info; TYPE_2__* version; } ;
struct TYPE_3__ {int /*<<< orphan*/  patch; int /*<<< orphan*/  ver; } ;
struct TYPE_4__ {TYPE_1__ app; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCGX_RAB_DEVICE_MODE ; 
 int /*<<< orphan*/  CCGX_RAB_READ_ALL_VER ; 
 int CCG_VERSION (int /*<<< orphan*/ ) ; 
 int CCG_VERSION_PATCH (int /*<<< orphan*/ ) ; 
 size_t FW2 ; 
 int ccg_read (struct ucsi_ccg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int get_fw_info(struct ucsi_ccg *uc)
{
	int err;

	err = ccg_read(uc, CCGX_RAB_READ_ALL_VER, (u8 *)(&uc->version),
		       sizeof(uc->version));
	if (err < 0)
		return err;

	uc->fw_version = CCG_VERSION(uc->version[FW2].app.ver) |
			CCG_VERSION_PATCH(uc->version[FW2].app.patch);

	err = ccg_read(uc, CCGX_RAB_DEVICE_MODE, (u8 *)(&uc->info),
		       sizeof(uc->info));
	if (err < 0)
		return err;

	return 0;
}