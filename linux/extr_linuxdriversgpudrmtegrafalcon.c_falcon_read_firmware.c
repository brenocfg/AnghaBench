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
struct TYPE_2__ {int /*<<< orphan*/  firmware; } ;
struct falcon {int /*<<< orphan*/  dev; TYPE_1__ firmware; } ;

/* Variables and functions */
 int request_firmware (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

int falcon_read_firmware(struct falcon *falcon, const char *name)
{
	int err;

	/* request_firmware prints error if it fails */
	err = request_firmware(&falcon->firmware.firmware, name, falcon->dev);
	if (err < 0)
		return err;

	return 0;
}