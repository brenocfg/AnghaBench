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
struct nfp_net {int id; int /*<<< orphan*/ * r_vecs; int /*<<< orphan*/  max_r_vecs; int /*<<< orphan*/  max_tx_rings; int /*<<< orphan*/  max_rx_rings; struct dentry* debugfs_dir; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 void* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_dir ; 
 scalar_t__ nfp_net_is_data_vnic (struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_rx_q_fops ; 
 int /*<<< orphan*/  nfp_tx_q_fops ; 
 int /*<<< orphan*/  nfp_xdp_q_fops ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void nfp_net_debugfs_vnic_add(struct nfp_net *nn, struct dentry *ddir)
{
	struct dentry *queues, *tx, *rx, *xdp;
	char name[20];
	int i;

	if (IS_ERR_OR_NULL(nfp_dir))
		return;

	if (nfp_net_is_data_vnic(nn))
		sprintf(name, "vnic%d", nn->id);
	else
		strcpy(name, "ctrl-vnic");
	nn->debugfs_dir = debugfs_create_dir(name, ddir);

	/* Create queue debugging sub-tree */
	queues = debugfs_create_dir("queue", nn->debugfs_dir);

	rx = debugfs_create_dir("rx", queues);
	tx = debugfs_create_dir("tx", queues);
	xdp = debugfs_create_dir("xdp", queues);

	for (i = 0; i < min(nn->max_rx_rings, nn->max_r_vecs); i++) {
		sprintf(name, "%d", i);
		debugfs_create_file(name, 0400, rx,
				    &nn->r_vecs[i], &nfp_rx_q_fops);
		debugfs_create_file(name, 0400, xdp,
				    &nn->r_vecs[i], &nfp_xdp_q_fops);
	}

	for (i = 0; i < min(nn->max_tx_rings, nn->max_r_vecs); i++) {
		sprintf(name, "%d", i);
		debugfs_create_file(name, 0400, tx,
				    &nn->r_vecs[i], &nfp_tx_q_fops);
	}
}