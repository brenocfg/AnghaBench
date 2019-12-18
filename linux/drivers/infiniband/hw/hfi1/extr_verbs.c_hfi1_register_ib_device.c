#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * parent; } ;
struct ib_device {unsigned int phys_port_cnt; int /*<<< orphan*/  num_comp_vectors; int /*<<< orphan*/  node_desc; TYPE_1__ dev; scalar_t__ node_guid; } ;
struct hfi1_ibport {int /*<<< orphan*/  rvp; } ;
struct hfi1_pportdata {int /*<<< orphan*/  pkeys; struct hfi1_ibport ibport_data; } ;
struct TYPE_12__ {int qpn_inc; int qpn_res_start; int qpn_res_end; int core_cap_flags; unsigned int nports; int reserved_operations; int /*<<< orphan*/  extra_rdma_atomic; int /*<<< orphan*/  wss_clean_period; int /*<<< orphan*/  wss_threshold; int /*<<< orphan*/  sge_copy_mode; int /*<<< orphan*/  npkeys; int /*<<< orphan*/  lkey_table_size; int /*<<< orphan*/  node; int /*<<< orphan*/  max_mad_size; int /*<<< orphan*/  psn_modify_mask; int /*<<< orphan*/  psn_shift; int /*<<< orphan*/  psn_mask; int /*<<< orphan*/  max_rdma_atomic; int /*<<< orphan*/  qos_shift; scalar_t__ qpn_start; int /*<<< orphan*/  qp_table_size; } ;
struct TYPE_11__ {int /*<<< orphan*/  comp_vect_cpu_lookup; int /*<<< orphan*/  setup_wqe; int /*<<< orphan*/  notify_restart_rc; int /*<<< orphan*/  modify_qp; int /*<<< orphan*/  check_modify_qp; int /*<<< orphan*/  mtu_to_path_mtu; int /*<<< orphan*/  mtu_from_qp; void* notify_error_qp; int /*<<< orphan*/  quiesce_qp; int /*<<< orphan*/  stop_send_queue; int /*<<< orphan*/  flush_qp_waiters; int /*<<< orphan*/  get_pmtu_from_attr; int /*<<< orphan*/  schedule_send_no_lock; int /*<<< orphan*/  schedule_send; int /*<<< orphan*/  do_send; int /*<<< orphan*/  notify_qp_reset; int /*<<< orphan*/  free_all_qps; int /*<<< orphan*/  qp_priv_free; int /*<<< orphan*/  qp_priv_init; int /*<<< orphan*/  qp_priv_alloc; int /*<<< orphan*/  cap_mask_chg; int /*<<< orphan*/  shut_down_port; int /*<<< orphan*/  query_port_state; int /*<<< orphan*/  get_guid_be; int /*<<< orphan*/  notify_new_ah; int /*<<< orphan*/  check_ah; int /*<<< orphan*/  get_pci_dev; } ;
struct TYPE_13__ {struct ib_device ibdev; int /*<<< orphan*/  wc_opcode; int /*<<< orphan*/  post_parms; TYPE_4__ dparms; scalar_t__ flags; TYPE_3__ driver_f; } ;
struct hfi1_ibdev {TYPE_5__ rdi; int /*<<< orphan*/  memwait; int /*<<< orphan*/  txwait; int /*<<< orphan*/  txwait_lock; int /*<<< orphan*/  iowait_lock; int /*<<< orphan*/  mem_timer; } ;
struct hfi1_devdata {unsigned int num_pports; struct hfi1_ibdev verbs_dev; struct hfi1_pportdata* pport; int /*<<< orphan*/  node; int /*<<< orphan*/  comp_vect_possible_cpus; int /*<<< orphan*/  qos_shift; TYPE_2__* pcidev; } ;
struct TYPE_14__ {int /*<<< orphan*/  nodename; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_MAX_RDMA_ATOMIC ; 
 int /*<<< orphan*/  HFI1_PORT_GUID_INDEX ; 
 int /*<<< orphan*/  HFI1_TID_RDMA_WRITE_CNT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPA_MGMT_MAD_SIZE ; 
 int /*<<< orphan*/  PSN_MASK ; 
 int /*<<< orphan*/  PSN_MODIFY_MASK ; 
 int /*<<< orphan*/  PSN_SHIFT ; 
 int RDMA_CORE_CAP_OPA_AH ; 
 int RDMA_CORE_PORT_INTEL_OPA ; 
 int /*<<< orphan*/  _hfi1_schedule_send ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int) ; 
 int /*<<< orphan*/  flush_qp_waiters ; 
 int /*<<< orphan*/  free_all_qps ; 
 int /*<<< orphan*/  get_pci_dev ; 
 int /*<<< orphan*/  get_pmtu_from_attr ; 
 scalar_t__ get_sguid (struct hfi1_ibport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_cap_mask_chg ; 
 int /*<<< orphan*/  hfi1_check_ah ; 
 int /*<<< orphan*/  hfi1_check_modify_qp ; 
 int /*<<< orphan*/  hfi1_comp_vect_mappings_lookup ; 
 int /*<<< orphan*/  hfi1_dev_ops ; 
 int /*<<< orphan*/  hfi1_do_send_from_rvt ; 
 int /*<<< orphan*/  hfi1_fill_device_attr (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  hfi1_get_guid_be ; 
 int /*<<< orphan*/  hfi1_get_npkeys (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  hfi1_lkey_table_size ; 
 int /*<<< orphan*/  hfi1_modify_qp ; 
 int /*<<< orphan*/  hfi1_notify_new_ah ; 
 int /*<<< orphan*/  hfi1_post_parms ; 
 int /*<<< orphan*/  hfi1_qp_priv_init ; 
 int /*<<< orphan*/  hfi1_qp_table_size ; 
 int /*<<< orphan*/  hfi1_restart_rc ; 
 int /*<<< orphan*/  hfi1_schedule_send ; 
 int /*<<< orphan*/  hfi1_setup_wqe ; 
 int hfi1_verbs_register_sysfs (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  ib_hfi1_attr_group ; 
 scalar_t__ ib_hfi1_sys_image_guid ; 
 int /*<<< orphan*/  ib_hfi1_wc_opcode ; 
 int /*<<< orphan*/  ib_set_device_ops (struct ib_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_ibport (struct hfi1_pportdata*) ; 
 TYPE_8__* init_utsname () ; 
 int kdeth_qp ; 
 int /*<<< orphan*/  mem_timer ; 
 int /*<<< orphan*/  mtu_from_qp ; 
 int /*<<< orphan*/  mtu_to_path_mtu ; 
 void* notify_error_qp ; 
 int /*<<< orphan*/  notify_qp_reset ; 
 int /*<<< orphan*/  qp_priv_alloc ; 
 int /*<<< orphan*/  qp_priv_free ; 
 int /*<<< orphan*/  query_port ; 
 int /*<<< orphan*/  quiesce_qp ; 
 int /*<<< orphan*/  rdma_set_device_sysfs_group (struct ib_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_init_port (TYPE_5__*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int rvt_register_device (TYPE_5__*) ; 
 int /*<<< orphan*/  rvt_unregister_device (TYPE_5__*) ; 
 int /*<<< orphan*/  seqlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sge_copy_mode ; 
 int /*<<< orphan*/  shut_down_port ; 
 int /*<<< orphan*/  stop_send_queue ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbs_txreq_exit (struct hfi1_ibdev*) ; 
 int verbs_txreq_init (struct hfi1_ibdev*) ; 
 int /*<<< orphan*/  wss_clean_period ; 
 int /*<<< orphan*/  wss_threshold ; 

int hfi1_register_ib_device(struct hfi1_devdata *dd)
{
	struct hfi1_ibdev *dev = &dd->verbs_dev;
	struct ib_device *ibdev = &dev->rdi.ibdev;
	struct hfi1_pportdata *ppd = dd->pport;
	struct hfi1_ibport *ibp = &ppd->ibport_data;
	unsigned i;
	int ret;

	for (i = 0; i < dd->num_pports; i++)
		init_ibport(ppd + i);

	/* Only need to initialize non-zero fields. */

	timer_setup(&dev->mem_timer, mem_timer, 0);

	seqlock_init(&dev->iowait_lock);
	seqlock_init(&dev->txwait_lock);
	INIT_LIST_HEAD(&dev->txwait);
	INIT_LIST_HEAD(&dev->memwait);

	ret = verbs_txreq_init(dev);
	if (ret)
		goto err_verbs_txreq;

	/* Use first-port GUID as node guid */
	ibdev->node_guid = get_sguid(ibp, HFI1_PORT_GUID_INDEX);

	/*
	 * The system image GUID is supposed to be the same for all
	 * HFIs in a single system but since there can be other
	 * device types in the system, we can't be sure this is unique.
	 */
	if (!ib_hfi1_sys_image_guid)
		ib_hfi1_sys_image_guid = ibdev->node_guid;
	ibdev->phys_port_cnt = dd->num_pports;
	ibdev->dev.parent = &dd->pcidev->dev;

	ib_set_device_ops(ibdev, &hfi1_dev_ops);

	strlcpy(ibdev->node_desc, init_utsname()->nodename,
		sizeof(ibdev->node_desc));

	/*
	 * Fill in rvt info object.
	 */
	dd->verbs_dev.rdi.driver_f.get_pci_dev = get_pci_dev;
	dd->verbs_dev.rdi.driver_f.check_ah = hfi1_check_ah;
	dd->verbs_dev.rdi.driver_f.notify_new_ah = hfi1_notify_new_ah;
	dd->verbs_dev.rdi.driver_f.get_guid_be = hfi1_get_guid_be;
	dd->verbs_dev.rdi.driver_f.query_port_state = query_port;
	dd->verbs_dev.rdi.driver_f.shut_down_port = shut_down_port;
	dd->verbs_dev.rdi.driver_f.cap_mask_chg = hfi1_cap_mask_chg;
	/*
	 * Fill in rvt info device attributes.
	 */
	hfi1_fill_device_attr(dd);

	/* queue pair */
	dd->verbs_dev.rdi.dparms.qp_table_size = hfi1_qp_table_size;
	dd->verbs_dev.rdi.dparms.qpn_start = 0;
	dd->verbs_dev.rdi.dparms.qpn_inc = 1;
	dd->verbs_dev.rdi.dparms.qos_shift = dd->qos_shift;
	dd->verbs_dev.rdi.dparms.qpn_res_start = kdeth_qp << 16;
	dd->verbs_dev.rdi.dparms.qpn_res_end =
	dd->verbs_dev.rdi.dparms.qpn_res_start + 65535;
	dd->verbs_dev.rdi.dparms.max_rdma_atomic = HFI1_MAX_RDMA_ATOMIC;
	dd->verbs_dev.rdi.dparms.psn_mask = PSN_MASK;
	dd->verbs_dev.rdi.dparms.psn_shift = PSN_SHIFT;
	dd->verbs_dev.rdi.dparms.psn_modify_mask = PSN_MODIFY_MASK;
	dd->verbs_dev.rdi.dparms.core_cap_flags = RDMA_CORE_PORT_INTEL_OPA |
						RDMA_CORE_CAP_OPA_AH;
	dd->verbs_dev.rdi.dparms.max_mad_size = OPA_MGMT_MAD_SIZE;

	dd->verbs_dev.rdi.driver_f.qp_priv_alloc = qp_priv_alloc;
	dd->verbs_dev.rdi.driver_f.qp_priv_init = hfi1_qp_priv_init;
	dd->verbs_dev.rdi.driver_f.qp_priv_free = qp_priv_free;
	dd->verbs_dev.rdi.driver_f.free_all_qps = free_all_qps;
	dd->verbs_dev.rdi.driver_f.notify_qp_reset = notify_qp_reset;
	dd->verbs_dev.rdi.driver_f.do_send = hfi1_do_send_from_rvt;
	dd->verbs_dev.rdi.driver_f.schedule_send = hfi1_schedule_send;
	dd->verbs_dev.rdi.driver_f.schedule_send_no_lock = _hfi1_schedule_send;
	dd->verbs_dev.rdi.driver_f.get_pmtu_from_attr = get_pmtu_from_attr;
	dd->verbs_dev.rdi.driver_f.notify_error_qp = notify_error_qp;
	dd->verbs_dev.rdi.driver_f.flush_qp_waiters = flush_qp_waiters;
	dd->verbs_dev.rdi.driver_f.stop_send_queue = stop_send_queue;
	dd->verbs_dev.rdi.driver_f.quiesce_qp = quiesce_qp;
	dd->verbs_dev.rdi.driver_f.notify_error_qp = notify_error_qp;
	dd->verbs_dev.rdi.driver_f.mtu_from_qp = mtu_from_qp;
	dd->verbs_dev.rdi.driver_f.mtu_to_path_mtu = mtu_to_path_mtu;
	dd->verbs_dev.rdi.driver_f.check_modify_qp = hfi1_check_modify_qp;
	dd->verbs_dev.rdi.driver_f.modify_qp = hfi1_modify_qp;
	dd->verbs_dev.rdi.driver_f.notify_restart_rc = hfi1_restart_rc;
	dd->verbs_dev.rdi.driver_f.setup_wqe = hfi1_setup_wqe;
	dd->verbs_dev.rdi.driver_f.comp_vect_cpu_lookup =
						hfi1_comp_vect_mappings_lookup;

	/* completeion queue */
	dd->verbs_dev.rdi.ibdev.num_comp_vectors = dd->comp_vect_possible_cpus;
	dd->verbs_dev.rdi.dparms.node = dd->node;

	/* misc settings */
	dd->verbs_dev.rdi.flags = 0; /* Let rdmavt handle it all */
	dd->verbs_dev.rdi.dparms.lkey_table_size = hfi1_lkey_table_size;
	dd->verbs_dev.rdi.dparms.nports = dd->num_pports;
	dd->verbs_dev.rdi.dparms.npkeys = hfi1_get_npkeys(dd);
	dd->verbs_dev.rdi.dparms.sge_copy_mode = sge_copy_mode;
	dd->verbs_dev.rdi.dparms.wss_threshold = wss_threshold;
	dd->verbs_dev.rdi.dparms.wss_clean_period = wss_clean_period;
	dd->verbs_dev.rdi.dparms.reserved_operations = 1;
	dd->verbs_dev.rdi.dparms.extra_rdma_atomic = HFI1_TID_RDMA_WRITE_CNT;

	/* post send table */
	dd->verbs_dev.rdi.post_parms = hfi1_post_parms;

	/* opcode translation table */
	dd->verbs_dev.rdi.wc_opcode = ib_hfi1_wc_opcode;

	ppd = dd->pport;
	for (i = 0; i < dd->num_pports; i++, ppd++)
		rvt_init_port(&dd->verbs_dev.rdi,
			      &ppd->ibport_data.rvp,
			      i,
			      ppd->pkeys);

	rdma_set_device_sysfs_group(&dd->verbs_dev.rdi.ibdev,
				    &ib_hfi1_attr_group);

	ret = rvt_register_device(&dd->verbs_dev.rdi);
	if (ret)
		goto err_verbs_txreq;

	ret = hfi1_verbs_register_sysfs(dd);
	if (ret)
		goto err_class;

	return ret;

err_class:
	rvt_unregister_device(&dd->verbs_dev.rdi);
err_verbs_txreq:
	verbs_txreq_exit(dev);
	dd_dev_err(dd, "cannot register verbs: %d!\n", -ret);
	return ret;
}