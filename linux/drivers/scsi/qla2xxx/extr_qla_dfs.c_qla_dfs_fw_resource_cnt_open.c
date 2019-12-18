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
struct scsi_qla_host {int dummy; } ;
struct inode {struct scsi_qla_host* i_private; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qla_dfs_fw_resource_cnt_show ; 
 int single_open (struct file*,int /*<<< orphan*/ ,struct scsi_qla_host*) ; 

__attribute__((used)) static int
qla_dfs_fw_resource_cnt_open(struct inode *inode, struct file *file)
{
	struct scsi_qla_host *vha = inode->i_private;

	return single_open(file, qla_dfs_fw_resource_cnt_show, vha);
}