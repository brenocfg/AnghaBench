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
struct cma3000_accl_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMA3000_CTRL ; 
 int CMA3000_SET (struct cma3000_accl_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CMA3000_SETDELAY ; 
 int /*<<< orphan*/  CMAMODE_POFF ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cma3000_poweroff(struct cma3000_accl_data *data)
{
	int ret;

	ret = CMA3000_SET(data, CMA3000_CTRL, CMAMODE_POFF, "Mode setting");
	msleep(CMA3000_SETDELAY);

	return ret;
}