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
typedef  int /*<<< orphan*/  u16 ;
struct omap_i2c_dev {int /*<<< orphan*/  cmd_complete; int /*<<< orphan*/  cmd_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
omap_i2c_complete_cmd(struct omap_i2c_dev *omap, u16 err)
{
	omap->cmd_err |= err;
	complete(&omap->cmd_complete);
}