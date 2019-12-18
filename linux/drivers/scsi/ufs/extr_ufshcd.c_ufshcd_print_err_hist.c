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
struct ufs_hba {int /*<<< orphan*/  dev; } ;
struct ufs_err_reg_hist {int pos; scalar_t__* reg; int /*<<< orphan*/ * tstamp; } ;

/* Variables and functions */
 int UFS_ERR_REG_HIST_LENGTH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  ktime_to_us (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ufshcd_print_err_hist(struct ufs_hba *hba,
				  struct ufs_err_reg_hist *err_hist,
				  char *err_name)
{
	int i;
	bool found = false;

	for (i = 0; i < UFS_ERR_REG_HIST_LENGTH; i++) {
		int p = (i + err_hist->pos) % UFS_ERR_REG_HIST_LENGTH;

		if (err_hist->reg[p] == 0)
			continue;
		dev_err(hba->dev, "%s[%d] = 0x%x at %lld us\n", err_name, p,
			err_hist->reg[p], ktime_to_us(err_hist->tstamp[p]));
		found = true;
	}

	if (!found)
		dev_err(hba->dev, "No record of %s errors\n", err_name);
}