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
struct ufs_hba {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 

void ufshcd_dealloc_host(struct ufs_hba *hba)
{
	scsi_host_put(hba->host);
}