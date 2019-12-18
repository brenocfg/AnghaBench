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
struct stmfx {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMFX_BOOT_TIME_MS ; 
 int /*<<< orphan*/  STMFX_REG_SYS_CTRL ; 
 int /*<<< orphan*/  STMFX_REG_SYS_CTRL_SWRST ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmfx_chip_reset(struct stmfx *stmfx)
{
	int ret;

	ret = regmap_write(stmfx->map, STMFX_REG_SYS_CTRL,
			   STMFX_REG_SYS_CTRL_SWRST);
	if (ret)
		return ret;

	msleep(STMFX_BOOT_TIME_MS);

	return ret;
}