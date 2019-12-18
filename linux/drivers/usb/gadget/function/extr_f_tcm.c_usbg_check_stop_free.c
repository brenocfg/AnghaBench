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
struct se_cmd {int dummy; } ;

/* Variables and functions */
 int target_put_sess_cmd (struct se_cmd*) ; 

__attribute__((used)) static int usbg_check_stop_free(struct se_cmd *se_cmd)
{
	return target_put_sess_cmd(se_cmd);
}