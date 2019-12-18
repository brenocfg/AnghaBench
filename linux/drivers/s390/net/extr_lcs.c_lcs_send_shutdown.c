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
struct lcs_cmd {int /*<<< orphan*/  initiator; int /*<<< orphan*/  cmd_code; } ;
struct lcs_card {int dummy; } ;
struct lcs_buffer {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCS_CMD_SHUTDOWN ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LCS_INITIATOR_TCPIP ; 
 int /*<<< orphan*/  LCS_STD_CMD_SIZE ; 
 struct lcs_buffer* lcs_get_lancmd (struct lcs_card*,int /*<<< orphan*/ ) ; 
 int lcs_send_lancmd (struct lcs_card*,struct lcs_buffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static int
lcs_send_shutdown(struct lcs_card *card)
{
	struct lcs_buffer *buffer;
	struct lcs_cmd *cmd;

	LCS_DBF_TEXT(2, trace, "shutdown");
	buffer = lcs_get_lancmd(card, LCS_STD_CMD_SIZE);
	cmd = (struct lcs_cmd *) buffer->data;
	cmd->cmd_code = LCS_CMD_SHUTDOWN;
	cmd->initiator = LCS_INITIATOR_TCPIP;
	return lcs_send_lancmd(card, buffer, NULL);
}