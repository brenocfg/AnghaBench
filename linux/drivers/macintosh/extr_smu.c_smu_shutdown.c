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
struct smu_simple_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_CMD_POWER_COMMAND ; 
 int /*<<< orphan*/ * smu ; 
 scalar_t__ smu_queue_simple (struct smu_simple_cmd*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char,char,unsigned char,char,char,char,char,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu_spinwait_simple (struct smu_simple_cmd*) ; 

void smu_shutdown(void)
{
	struct smu_simple_cmd cmd;

	if (smu == NULL)
		return;

	if (smu_queue_simple(&cmd, SMU_CMD_POWER_COMMAND, 9, NULL, NULL,
			     'S', 'H', 'U', 'T', 'D', 'O', 'W', 'N', 0))
		return;
	smu_spinwait_simple(&cmd);
	for (;;)
		;
}