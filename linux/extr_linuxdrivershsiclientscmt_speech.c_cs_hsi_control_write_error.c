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
struct hsi_msg {int dummy; } ;
struct cs_hsi_iface {int /*<<< orphan*/  control_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cs_hsi_error_post (struct cs_hsi_iface*) ; 
 int /*<<< orphan*/  __cs_hsi_error_pre (struct cs_hsi_iface*,struct hsi_msg*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __cs_hsi_error_write_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs_release_cmd (struct hsi_msg*) ; 

__attribute__((used)) static void cs_hsi_control_write_error(struct cs_hsi_iface *hi,
							struct hsi_msg *msg)
{
	__cs_hsi_error_pre(hi, msg, "control write", &hi->control_state);
	cs_release_cmd(msg);
	__cs_hsi_error_write_bits(&hi->control_state);
	__cs_hsi_error_post(hi);

}