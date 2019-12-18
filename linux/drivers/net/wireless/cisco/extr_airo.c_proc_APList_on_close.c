#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct proc_data {int writelen; scalar_t__ wbuffer; } ;
struct net_device {struct airo_info* ml_priv; } ;
struct inode {int dummy; } ;
struct file {struct proc_data* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ap; int /*<<< orphan*/  len; } ;
struct airo_info {TYPE_1__ APList; } ;
typedef  TYPE_1__ APListRid ;

/* Variables and functions */
 struct net_device* PDE_DATA (struct inode*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  disable_MAC (struct airo_info*,int) ; 
 int /*<<< orphan*/  enable_MAC (struct airo_info*,int) ; 
 int /*<<< orphan*/  mac_pton (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writeAPListRid (struct airo_info*,TYPE_1__*,int) ; 

__attribute__((used)) static void proc_APList_on_close( struct inode *inode, struct file *file ) {
	struct proc_data *data = file->private_data;
	struct net_device *dev = PDE_DATA(inode);
	struct airo_info *ai = dev->ml_priv;
	APListRid *APList_rid = &ai->APList;
	int i;

	if ( !data->writelen ) return;

	memset(APList_rid, 0, sizeof(*APList_rid));
	APList_rid->len = cpu_to_le16(sizeof(*APList_rid));

	for (i = 0; i < 4 && data->writelen >= (i + 1) * 6 * 3; i++)
		mac_pton(data->wbuffer + i * 6 * 3, APList_rid->ap[i]);

	disable_MAC(ai, 1);
	writeAPListRid(ai, APList_rid, 1);
	enable_MAC(ai, 1);
}