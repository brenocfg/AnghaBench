#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ft_cmd {int /*<<< orphan*/  req_frame; TYPE_2__* sess; } ;
typedef  enum fcp_resp_rsp_codes { ____Placeholder_fcp_resp_rsp_codes } fcp_resp_rsp_codes ;
struct TYPE_4__ {TYPE_1__* tport; } ;
struct TYPE_3__ {int /*<<< orphan*/  lport; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 int /*<<< orphan*/  ft_send_resp_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ft_send_resp_code(struct ft_cmd *cmd,
			      enum fcp_resp_rsp_codes code)
{
	ft_send_resp_status(cmd->sess->tport->lport,
			    cmd->req_frame, SAM_STAT_GOOD, code);
}