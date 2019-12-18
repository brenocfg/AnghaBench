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
struct ctlr_info {TYPE_2__* pdev; int /*<<< orphan*/  legacy_board; } ;
struct ReportLUNdata {int extended_response_flag; } ;
struct ErrorInfo {scalar_t__ CommandStatus; } ;
struct TYPE_3__ {int* CDB; } ;
struct CommandList {struct ErrorInfo* err_info; TYPE_1__ Request; } ;
typedef  int /*<<< orphan*/  scsi3addr ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CMD_DATA_UNDERRUN ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HPSA_REPORT_LOG ; 
 int /*<<< orphan*/  HPSA_REPORT_PHYS ; 
 int IO_OK ; 
 int /*<<< orphan*/  NO_TIMEOUT ; 
 int /*<<< orphan*/  TYPE_CMD ; 
 struct CommandList* cmd_alloc (struct ctlr_info*) ; 
 int /*<<< orphan*/  cmd_free (struct ctlr_info*,struct CommandList*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 scalar_t__ fill_cmd (struct CommandList*,int /*<<< orphan*/ ,struct ctlr_info*,void*,int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int hpsa_scsi_do_simple_cmd_with_retry (struct ctlr_info*,struct CommandList*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsa_scsi_interpret_error (struct ctlr_info*,struct CommandList*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hpsa_scsi_do_report_luns(struct ctlr_info *h, int logical,
		void *buf, int bufsize,
		int extended_response)
{
	int rc = IO_OK;
	struct CommandList *c;
	unsigned char scsi3addr[8];
	struct ErrorInfo *ei;

	c = cmd_alloc(h);

	/* address the controller */
	memset(scsi3addr, 0, sizeof(scsi3addr));
	if (fill_cmd(c, logical ? HPSA_REPORT_LOG : HPSA_REPORT_PHYS, h,
		buf, bufsize, 0, scsi3addr, TYPE_CMD)) {
		rc = -EAGAIN;
		goto out;
	}
	if (extended_response)
		c->Request.CDB[1] = extended_response;
	rc = hpsa_scsi_do_simple_cmd_with_retry(h, c, DMA_FROM_DEVICE,
			NO_TIMEOUT);
	if (rc)
		goto out;
	ei = c->err_info;
	if (ei->CommandStatus != 0 &&
	    ei->CommandStatus != CMD_DATA_UNDERRUN) {
		hpsa_scsi_interpret_error(h, c);
		rc = -EIO;
	} else {
		struct ReportLUNdata *rld = buf;

		if (rld->extended_response_flag != extended_response) {
			if (!h->legacy_board) {
				dev_err(&h->pdev->dev,
					"report luns requested format %u, got %u\n",
					extended_response,
					rld->extended_response_flag);
				rc = -EINVAL;
			} else
				rc = -EOPNOTSUPP;
		}
	}
out:
	cmd_free(h, c);
	return rc;
}