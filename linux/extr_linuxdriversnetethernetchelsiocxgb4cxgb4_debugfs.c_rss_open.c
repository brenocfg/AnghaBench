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
typedef  int /*<<< orphan*/  u16 ;
struct seq_tab {scalar_t__ data; } ;
struct inode {struct adapter* i_private; } ;
struct file {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  rss_show ; 
 struct seq_tab* seq_open_tab (struct file*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_release_private (struct inode*,struct file*) ; 
 int t4_chip_rss_size (struct adapter*) ; 
 int t4_read_rss (struct adapter*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rss_open(struct inode *inode, struct file *file)
{
	struct adapter *adap = inode->i_private;
	int ret, nentries;
	struct seq_tab *p;

	nentries = t4_chip_rss_size(adap);
	p = seq_open_tab(file, nentries / 8, 8 * sizeof(u16), 0, rss_show);
	if (!p)
		return -ENOMEM;

	ret = t4_read_rss(adap, (u16 *)p->data);
	if (ret)
		seq_release_private(inode, file);

	return ret;
}