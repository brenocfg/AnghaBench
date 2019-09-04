#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hfi1_pportdata {int unit; int num_pports; struct hfi1_pportdata* pport; } ;
struct hfi1_ibdev {int /*<<< orphan*/  hfi1_ibdev_dbg; int /*<<< orphan*/  hfi1_ibdev_link; } ;
struct hfi1_devdata {int unit; int num_pports; struct hfi1_devdata* pport; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  link ;
struct TYPE_6__ {int /*<<< orphan*/  write; } ;
struct TYPE_5__ {char* name; TYPE_3__ ops; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DEBUGFS_FILE_CREATE (char*,int /*<<< orphan*/ ,struct hfi1_pportdata*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  DEBUGFS_SEQ_FILE_CREATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hfi1_ibdev*) ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 char* class_name () ; 
 TYPE_1__* cntr_ops ; 
 int /*<<< orphan*/  ctx_stats ; 
 struct hfi1_pportdata* dd_from_dev (struct hfi1_ibdev*) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_symlink (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hfi1_dbg_root ; 
 int /*<<< orphan*/  hfi1_fault_init_debugfs (struct hfi1_ibdev*) ; 
 int /*<<< orphan*/  opcode_stats ; 
 TYPE_1__* port_cntr_ops ; 
 int /*<<< orphan*/  pr_warn (char*,char*) ; 
 int /*<<< orphan*/  qp_stats ; 
 int /*<<< orphan*/  rcds ; 
 int /*<<< orphan*/  sdes ; 
 int /*<<< orphan*/  sdma_cpu_list ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  tx_opcode_stats ; 

void hfi1_dbg_ibdev_init(struct hfi1_ibdev *ibd)
{
	char name[sizeof("port0counters") + 1];
	char link[10];
	struct hfi1_devdata *dd = dd_from_dev(ibd);
	struct hfi1_pportdata *ppd;
	int unit = dd->unit;
	int i, j;

	if (!hfi1_dbg_root)
		return;
	snprintf(name, sizeof(name), "%s_%d", class_name(), unit);
	snprintf(link, sizeof(link), "%d", unit);
	ibd->hfi1_ibdev_dbg = debugfs_create_dir(name, hfi1_dbg_root);
	if (!ibd->hfi1_ibdev_dbg) {
		pr_warn("create of %s failed\n", name);
		return;
	}
	ibd->hfi1_ibdev_link =
		debugfs_create_symlink(link, hfi1_dbg_root, name);
	if (!ibd->hfi1_ibdev_link) {
		pr_warn("create of %s symlink failed\n", name);
		return;
	}
	DEBUGFS_SEQ_FILE_CREATE(opcode_stats, ibd->hfi1_ibdev_dbg, ibd);
	DEBUGFS_SEQ_FILE_CREATE(tx_opcode_stats, ibd->hfi1_ibdev_dbg, ibd);
	DEBUGFS_SEQ_FILE_CREATE(ctx_stats, ibd->hfi1_ibdev_dbg, ibd);
	DEBUGFS_SEQ_FILE_CREATE(qp_stats, ibd->hfi1_ibdev_dbg, ibd);
	DEBUGFS_SEQ_FILE_CREATE(sdes, ibd->hfi1_ibdev_dbg, ibd);
	DEBUGFS_SEQ_FILE_CREATE(rcds, ibd->hfi1_ibdev_dbg, ibd);
	DEBUGFS_SEQ_FILE_CREATE(sdma_cpu_list, ibd->hfi1_ibdev_dbg, ibd);
	/* dev counter files */
	for (i = 0; i < ARRAY_SIZE(cntr_ops); i++)
		DEBUGFS_FILE_CREATE(cntr_ops[i].name,
				    ibd->hfi1_ibdev_dbg,
				    dd,
				    &cntr_ops[i].ops, S_IRUGO);
	/* per port files */
	for (ppd = dd->pport, j = 0; j < dd->num_pports; j++, ppd++)
		for (i = 0; i < ARRAY_SIZE(port_cntr_ops); i++) {
			snprintf(name,
				 sizeof(name),
				 port_cntr_ops[i].name,
				 j + 1);
			DEBUGFS_FILE_CREATE(name,
					    ibd->hfi1_ibdev_dbg,
					    ppd,
					    &port_cntr_ops[i].ops,
					    !port_cntr_ops[i].ops.write ?
					    S_IRUGO : S_IRUGO | S_IWUSR);
		}

	hfi1_fault_init_debugfs(ibd);
}