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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct mthca_mailbox {int /*<<< orphan*/  dma; } ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MGID_HASH ; 
 int /*<<< orphan*/  CMD_TIME_CLASS_A ; 
 int mthca_cmd_imm (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mthca_MGID_HASH(struct mthca_dev *dev, struct mthca_mailbox *mailbox,
		    u16 *hash)
{
	u64 imm;
	int err;

	err = mthca_cmd_imm(dev, mailbox->dma, &imm, 0, 0, CMD_MGID_HASH,
			    CMD_TIME_CLASS_A);

	*hash = imm;
	return err;
}