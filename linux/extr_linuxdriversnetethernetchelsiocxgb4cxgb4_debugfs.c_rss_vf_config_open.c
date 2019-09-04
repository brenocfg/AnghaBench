#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_tab {scalar_t__ data; } ;
struct rss_vf_conf {int /*<<< orphan*/  rss_vf_vfh; int /*<<< orphan*/  rss_vf_vfl; } ;
struct inode {struct adapter* i_private; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int vfcount; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  rss_vf_config_show ; 
 struct seq_tab* seq_open_tab (struct file*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_rss_vf_config (struct adapter*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rss_vf_config_open(struct inode *inode, struct file *file)
{
	struct adapter *adapter = inode->i_private;
	struct seq_tab *p;
	struct rss_vf_conf *vfconf;
	int vf, vfcount = adapter->params.arch.vfcount;

	p = seq_open_tab(file, vfcount, sizeof(*vfconf), 1, rss_vf_config_show);
	if (!p)
		return -ENOMEM;

	vfconf = (struct rss_vf_conf *)p->data;
	for (vf = 0; vf < vfcount; vf++) {
		t4_read_rss_vf_config(adapter, vf, &vfconf[vf].rss_vf_vfl,
				      &vfconf[vf].rss_vf_vfh, true);
	}
	return 0;
}