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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int major; int* minor; } ;
struct si476x_func_info {int patch_id; int func; TYPE_1__ firmware; } ;
struct si476x_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  CMD_FUNC_INFO ; 
 int CMD_FUNC_INFO_NRESP ; 
 int /*<<< orphan*/  SI476X_DEFAULT_TIMEOUT ; 
 int si476x_core_send_command (struct si476x_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int si476x_core_cmd_func_info(struct si476x_core *core,
			      struct si476x_func_info *info)
{
	int err;
	u8  resp[CMD_FUNC_INFO_NRESP];

	err = si476x_core_send_command(core, CMD_FUNC_INFO,
				       NULL, 0,
				       resp, ARRAY_SIZE(resp),
				       SI476X_DEFAULT_TIMEOUT);

	info->firmware.major    = resp[1];
	info->firmware.minor[0] = resp[2];
	info->firmware.minor[1] = resp[3];

	info->patch_id = ((u16) resp[4] << 8) | resp[5];
	info->func     = resp[6];

	return err;
}