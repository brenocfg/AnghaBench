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
struct a6xx_hfi_msg_test {int /*<<< orphan*/  member_0; } ;
struct a6xx_gmu {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_H2F_MSG_TEST ; 
 int a6xx_hfi_send_msg (struct a6xx_gmu*,int /*<<< orphan*/ ,struct a6xx_hfi_msg_test*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int a6xx_hfi_send_test(struct a6xx_gmu *gmu)
{
	struct a6xx_hfi_msg_test msg = { 0 };

	return a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_TEST, &msg, sizeof(msg),
		NULL, 0);
}