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
struct res_common {int /*<<< orphan*/  state; int /*<<< orphan*/  res_id; } ;
struct res_fs_rule {int qpn; struct res_common com; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RES_FS_RULE_ALLOCATED ; 
 struct res_fs_rule* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct res_common *alloc_fs_rule_tr(u64 id, int qpn)
{
	struct res_fs_rule *ret;

	ret = kzalloc(sizeof(*ret), GFP_KERNEL);
	if (!ret)
		return NULL;

	ret->com.res_id = id;
	ret->com.state = RES_FS_RULE_ALLOCATED;
	ret->qpn = qpn;
	return &ret->com;
}