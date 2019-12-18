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
typedef  int /*<<< orphan*/  u8 ;
struct ctlr_info {int dummy; } ;
struct ErrorInfo {scalar_t__ CommandStatus; } ;
struct CommandList {struct ErrorInfo* err_info; } ;

/* Variables and functions */
 scalar_t__ CMD_DATA_UNDERRUN ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int IO_OK ; 
 int /*<<< orphan*/  NO_TIMEOUT ; 
 int /*<<< orphan*/  RECEIVE_DIAGNOSTIC ; 
 int /*<<< orphan*/  TYPE_CMD ; 
 struct CommandList* cmd_alloc (struct ctlr_info*) ; 
 int /*<<< orphan*/  cmd_free (struct ctlr_info*,struct CommandList*) ; 
 scalar_t__ fill_cmd (struct CommandList*,int /*<<< orphan*/ ,struct ctlr_info*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hpsa_scsi_do_simple_cmd_with_retry (struct ctlr_info*,struct CommandList*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsa_scsi_interpret_error (struct ctlr_info*,struct CommandList*) ; 

__attribute__((used)) static int hpsa_do_receive_diagnostic(struct ctlr_info *h, u8 *scsi3addr,
					u8 page, u8 *buf, size_t bufsize)
{
	int rc = IO_OK;
	struct CommandList *c;
	struct ErrorInfo *ei;

	c = cmd_alloc(h);
	if (fill_cmd(c, RECEIVE_DIAGNOSTIC, h, buf, bufsize,
			page, scsi3addr, TYPE_CMD)) {
		rc = -1;
		goto out;
	}
	rc = hpsa_scsi_do_simple_cmd_with_retry(h, c, DMA_FROM_DEVICE,
			NO_TIMEOUT);
	if (rc)
		goto out;
	ei = c->err_info;
	if (ei->CommandStatus != 0 && ei->CommandStatus != CMD_DATA_UNDERRUN) {
		hpsa_scsi_interpret_error(h, c);
		rc = -1;
	}
out:
	cmd_free(h, c);
	return rc;
}