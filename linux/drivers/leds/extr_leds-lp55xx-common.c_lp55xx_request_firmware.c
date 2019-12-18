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
struct lp55xx_chip {TYPE_1__* cl; } ;
struct device {int dummy; } ;
struct TYPE_2__ {char* name; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  lp55xx_firmware_loaded ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,char const*,struct device*,int /*<<< orphan*/ ,struct lp55xx_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp55xx_request_firmware(struct lp55xx_chip *chip)
{
	const char *name = chip->cl->name;
	struct device *dev = &chip->cl->dev;

	return request_firmware_nowait(THIS_MODULE, false, name, dev,
				GFP_KERNEL, chip, lp55xx_firmware_loaded);
}