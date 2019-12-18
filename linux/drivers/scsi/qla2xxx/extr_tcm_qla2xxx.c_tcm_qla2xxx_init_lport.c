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
struct tcm_qla2xxx_lport {int /*<<< orphan*/  lport_fcport_map; int /*<<< orphan*/  lport_loopid_map; } ;
struct tcm_qla2xxx_fc_loopid {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  array_size (int,int) ; 
 int /*<<< orphan*/  btree_destroy32 (int /*<<< orphan*/ *) ; 
 int btree_init32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  vzalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcm_qla2xxx_init_lport(struct tcm_qla2xxx_lport *lport)
{
	int rc;

	rc = btree_init32(&lport->lport_fcport_map);
	if (rc) {
		pr_err("Unable to initialize lport->lport_fcport_map btree\n");
		return rc;
	}

	lport->lport_loopid_map =
		vzalloc(array_size(65536,
				   sizeof(struct tcm_qla2xxx_fc_loopid)));
	if (!lport->lport_loopid_map) {
		pr_err("Unable to allocate lport->lport_loopid_map of %zu bytes\n",
		    sizeof(struct tcm_qla2xxx_fc_loopid) * 65536);
		btree_destroy32(&lport->lport_fcport_map);
		return -ENOMEM;
	}
	pr_debug("qla2xxx: Allocated lport_loopid_map of %zu bytes\n",
	       sizeof(struct tcm_qla2xxx_fc_loopid) * 65536);
	return 0;
}