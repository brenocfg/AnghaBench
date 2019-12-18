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
struct inode {int /*<<< orphan*/ * i_private; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  qla2x00_dfs_tgt_port_database_show ; 
 int single_open (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qla2x00_dfs_tgt_port_database_open(struct inode *inode, struct file *file)
{
	scsi_qla_host_t *vha = inode->i_private;

	return single_open(file, qla2x00_dfs_tgt_port_database_show, vha);
}