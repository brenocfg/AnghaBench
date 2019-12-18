#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ntb_msit_ctx {TYPE_1__* peers; } ;
struct ntb_dev {struct ntb_msit_ctx* ctx; } ;
struct ntb_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  msi_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_clear_ctx (struct ntb_dev*) ; 
 int /*<<< orphan*/  ntb_db_set_mask (struct ntb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_db_valid_mask (struct ntb_dev*) ; 
 int /*<<< orphan*/  ntb_link_disable (struct ntb_dev*) ; 
 int /*<<< orphan*/  ntb_msi_clear_mws (struct ntb_dev*) ; 
 int /*<<< orphan*/  ntb_msit_remove_dbgfs (struct ntb_msit_ctx*) ; 
 int ntb_peer_port_count (struct ntb_dev*) ; 

__attribute__((used)) static void ntb_msit_remove(struct ntb_client *client, struct ntb_dev *ntb)
{
	struct ntb_msit_ctx *nm = ntb->ctx;
	int i;

	ntb_link_disable(ntb);
	ntb_db_set_mask(ntb, ntb_db_valid_mask(ntb));
	ntb_msi_clear_mws(ntb);

	for (i = 0; i < ntb_peer_port_count(ntb); i++)
		kfree(nm->peers[i].msi_desc);

	ntb_clear_ctx(ntb);
	ntb_msit_remove_dbgfs(nm);
}