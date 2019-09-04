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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  val; int /*<<< orphan*/  addr; } ;
struct lp55xx_device_config {TYPE_1__ reset; } ;
struct lp55xx_chip {struct lp55xx_device_config* cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  lp55xx_write (struct lp55xx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lp55xx_reset_device(struct lp55xx_chip *chip)
{
	struct lp55xx_device_config *cfg = chip->cfg;
	u8 addr = cfg->reset.addr;
	u8 val  = cfg->reset.val;

	/* no error checking here because no ACK from the device after reset */
	lp55xx_write(chip, addr, val);
}