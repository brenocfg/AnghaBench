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
struct scsi_device {scalar_t__ channel; scalar_t__ id; int /*<<< orphan*/  host; } ;
struct myrb_rbld_progress {scalar_t__ ldev_num; unsigned int ldev_size; unsigned int blocks_left; } ;
struct myrb_hba {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned short MYRB_STATUS_SUCCESS ; 
 unsigned short myrb_get_rbld_progress (struct myrb_hba*,struct myrb_rbld_progress*) ; 
 scalar_t__ myrb_logical_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myrb_raid_template ; 
 int /*<<< orphan*/  raid_set_resync (int /*<<< orphan*/ ,struct device*,unsigned int) ; 
 struct myrb_hba* shost_priv (int /*<<< orphan*/ ) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static void myrb_get_resync(struct device *dev)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	struct myrb_hba *cb = shost_priv(sdev->host);
	struct myrb_rbld_progress rbld_buf;
	unsigned int percent_complete = 0;
	unsigned short status;
	unsigned int ldev_size = 0, remaining = 0;

	if (sdev->channel < myrb_logical_channel(sdev->host))
		return;
	status = myrb_get_rbld_progress(cb, &rbld_buf);
	if (status == MYRB_STATUS_SUCCESS) {
		if (rbld_buf.ldev_num == sdev->id) {
			ldev_size = rbld_buf.ldev_size;
			remaining = rbld_buf.blocks_left;
		}
	}
	if (remaining && ldev_size)
		percent_complete = (ldev_size - remaining) * 100 / ldev_size;
	raid_set_resync(myrb_raid_template, dev, percent_complete);
}