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
struct ufs_hba {int nutrs; } ;
struct scsi_device {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int scsi_change_queue_depth (struct scsi_device*,int) ; 
 struct ufs_hba* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ufshcd_change_queue_depth(struct scsi_device *sdev, int depth)
{
	struct ufs_hba *hba = shost_priv(sdev->host);

	if (depth > hba->nutrs)
		depth = hba->nutrs;
	return scsi_change_queue_depth(sdev, depth);
}