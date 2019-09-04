#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  size_t ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_6__ {scalar_t__ blk0_len; scalar_t__ len; } ;
struct TYPE_7__ {size_t scp_data_len; scalar_t__ scp_data; } ;
struct TYPE_5__ {TYPE_3__ fcp; } ;
struct TYPE_8__ {TYPE_2__ hdr; TYPE_1__ ipl_info; } ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ IPL_PARM_BLK0_FCP_LEN ; 
 scalar_t__ IPL_PARM_BLK_FCP_LEN ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 TYPE_4__* reipl_block_fcp ; 

__attribute__((used)) static ssize_t reipl_fcp_scpdata_write(struct file *filp, struct kobject *kobj,
				       struct bin_attribute *attr,
				       char *buf, loff_t off, size_t count)
{
	size_t scpdata_len = count;
	size_t padding;


	if (off)
		return -EINVAL;

	memcpy(reipl_block_fcp->ipl_info.fcp.scp_data, buf, count);
	if (scpdata_len % 8) {
		padding = 8 - (scpdata_len % 8);
		memset(reipl_block_fcp->ipl_info.fcp.scp_data + scpdata_len,
		       0, padding);
		scpdata_len += padding;
	}

	reipl_block_fcp->ipl_info.fcp.scp_data_len = scpdata_len;
	reipl_block_fcp->hdr.len = IPL_PARM_BLK_FCP_LEN + scpdata_len;
	reipl_block_fcp->hdr.blk0_len = IPL_PARM_BLK0_FCP_LEN + scpdata_len;

	return count;
}