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
struct stmpe {int /*<<< orphan*/  domain; TYPE_1__* pdata; int /*<<< orphan*/  dev; } ;
struct mfd_cell {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int mfd_add_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mfd_cell const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmpe_add_device(struct stmpe *stmpe, const struct mfd_cell *cell)
{
	return mfd_add_devices(stmpe->dev, stmpe->pdata->id, cell, 1,
			       NULL, 0, stmpe->domain);
}