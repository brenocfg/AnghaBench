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
typedef  int /*<<< orphan*/  u32 ;
struct s3fwrn5_fw_version {scalar_t__ major; scalar_t__ build1; scalar_t__ build2; } ;
struct TYPE_2__ {int /*<<< orphan*/  version; } ;
struct s3fwrn5_fw_info {TYPE_1__ fw; } ;

/* Variables and functions */

bool s3fwrn5_fw_check_version(struct s3fwrn5_fw_info *fw_info, u32 version)
{
	struct s3fwrn5_fw_version *new = (void *) &fw_info->fw.version;
	struct s3fwrn5_fw_version *old = (void *) &version;

	if (new->major > old->major)
		return true;
	if (new->build1 > old->build1)
		return true;
	if (new->build2 > old->build2)
		return true;

	return false;
}