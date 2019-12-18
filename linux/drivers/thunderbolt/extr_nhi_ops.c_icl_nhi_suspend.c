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
struct tb_nhi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICL_LC_MAILBOX_TIMEOUT ; 
 int /*<<< orphan*/  ICL_LC_PREPARE_FOR_RESET ; 
 int icl_nhi_force_power (struct tb_nhi*,int) ; 
 scalar_t__ icl_nhi_is_device_connected (struct tb_nhi*) ; 
 int /*<<< orphan*/  icl_nhi_lc_mailbox_cmd (struct tb_nhi*,int /*<<< orphan*/ ) ; 
 int icl_nhi_lc_mailbox_cmd_complete (struct tb_nhi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int icl_nhi_suspend(struct tb_nhi *nhi)
{
	int ret;

	if (icl_nhi_is_device_connected(nhi))
		return 0;

	/*
	 * If there is no device connected we need to perform both: a
	 * handshake through LC mailbox and force power down before
	 * entering D3.
	 */
	icl_nhi_lc_mailbox_cmd(nhi, ICL_LC_PREPARE_FOR_RESET);
	ret = icl_nhi_lc_mailbox_cmd_complete(nhi, ICL_LC_MAILBOX_TIMEOUT);
	if (ret)
		return ret;

	return icl_nhi_force_power(nhi, false);
}