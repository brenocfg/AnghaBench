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
struct t10_pr_registration {int dummy; } ;
struct se_node_acl {int dummy; } ;
struct se_lun {int dummy; } ;
struct se_device {int dummy; } ;
struct se_dev_entry {int dummy; } ;
typedef  enum register_type { ____Placeholder_register_type } register_type ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  __core_scsi3_add_registration (struct se_device*,struct se_node_acl*,struct t10_pr_registration*,int,int) ; 
 struct t10_pr_registration* __core_scsi3_alloc_registration (struct se_device*,struct se_node_acl*,struct se_lun*,struct se_dev_entry*,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int core_scsi3_alloc_registration(
	struct se_device *dev,
	struct se_node_acl *nacl,
	struct se_lun *lun,
	struct se_dev_entry *deve,
	u64 mapped_lun,
	unsigned char *isid,
	u64 sa_res_key,
	int all_tg_pt,
	int aptpl,
	enum register_type register_type,
	int register_move)
{
	struct t10_pr_registration *pr_reg;

	pr_reg = __core_scsi3_alloc_registration(dev, nacl, lun, deve, mapped_lun,
						 isid, sa_res_key, all_tg_pt,
						 aptpl);
	if (!pr_reg)
		return -EPERM;

	__core_scsi3_add_registration(dev, nacl, pr_reg,
			register_type, register_move);
	return 0;
}