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
struct m5mols_info {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_EXECUTE ; 
 int /*<<< orphan*/  AF_MODE ; 
 int /*<<< orphan*/  REG_AF_IDLE ; 
 int /*<<< orphan*/  REG_AF_POWEROFF ; 
 int /*<<< orphan*/  REG_AF_STOP ; 
 int /*<<< orphan*/  SYSTEM_STATUS ; 
 int m5mols_busy_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int m5mols_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m5mols_auto_focus_stop(struct m5mols_info *info)
{
	int ret;

	ret = m5mols_write(&info->sd, AF_EXECUTE, REG_AF_STOP);
	if (!ret)
		ret = m5mols_write(&info->sd, AF_MODE, REG_AF_POWEROFF);
	if (!ret)
		ret = m5mols_busy_wait(&info->sd, SYSTEM_STATUS, REG_AF_IDLE,
				       0xff, -1);
	return ret;
}