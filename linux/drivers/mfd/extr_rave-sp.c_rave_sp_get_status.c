#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rave_sp_status {int /*<<< orphan*/  bootloader_version; int /*<<< orphan*/  firmware_version; } ;
struct rave_sp {char const* part_number_firmware; char const* part_number_bootloader; TYPE_3__* variant; TYPE_1__* serdev; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int (* get_status ) (struct rave_sp*,struct rave_sp_status*) ;} ;
struct TYPE_6__ {TYPE_2__ cmd; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 char* devm_rave_sp_version (struct device*,int /*<<< orphan*/ *) ; 
 int stub1 (struct rave_sp*,struct rave_sp_status*) ; 

__attribute__((used)) static int rave_sp_get_status(struct rave_sp *sp)
{
	struct device *dev = &sp->serdev->dev;
	struct rave_sp_status status;
	const char *version;
	int ret;

	ret = sp->variant->cmd.get_status(sp, &status);
	if (ret)
		return ret;

	version = devm_rave_sp_version(dev, &status.firmware_version);
	if (!version)
		return -ENOMEM;

	sp->part_number_firmware = version;

	version = devm_rave_sp_version(dev, &status.bootloader_version);
	if (!version)
		return -ENOMEM;

	sp->part_number_bootloader = version;

	return 0;
}