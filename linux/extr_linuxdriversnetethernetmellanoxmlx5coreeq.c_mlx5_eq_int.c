#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_18__ {int /*<<< orphan*/  num_pages; int /*<<< orphan*/  func_id; } ;
struct TYPE_17__ {int /*<<< orphan*/  syndrome; int /*<<< orphan*/  cqn; } ;
struct TYPE_16__ {int port; } ;
struct TYPE_15__ {int /*<<< orphan*/  vector; } ;
struct TYPE_14__ {int type; int /*<<< orphan*/  qp_srq_n; } ;
struct TYPE_13__ {int /*<<< orphan*/  dctn; } ;
struct TYPE_12__ {int /*<<< orphan*/  cqn; } ;
struct TYPE_20__ {int /*<<< orphan*/  raw; TYPE_7__ req_pages; TYPE_6__ cq_err; TYPE_5__ port; TYPE_4__ cmd; TYPE_3__ qp_srq; TYPE_2__ dct; TYPE_1__ comp; } ;
struct mlx5_eqe {int type; TYPE_9__ data; int /*<<< orphan*/  sub_type; } ;
struct TYPE_11__ {int /*<<< orphan*/  task; } ;
struct mlx5_eq {TYPE_10__ tasklet_ctx; int /*<<< orphan*/  cons_index; int /*<<< orphan*/  eqn; struct mlx5_core_dev* dev; } ;
struct TYPE_19__ {int /*<<< orphan*/  eswitch; } ;
struct mlx5_core_dev {TYPE_8__ priv; int /*<<< orphan*/  (* event ) (struct mlx5_core_dev*,int /*<<< orphan*/ ,unsigned long) ;} ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  MLX5_EVENT_TYPE_CMD 158 
#define  MLX5_EVENT_TYPE_COMM_EST 157 
#define  MLX5_EVENT_TYPE_COMP 156 
#define  MLX5_EVENT_TYPE_CQ_ERROR 155 
#define  MLX5_EVENT_TYPE_DCT_DRAINED 154 
#define  MLX5_EVENT_TYPE_DEVICE_TRACER 153 
#define  MLX5_EVENT_TYPE_FPGA_ERROR 152 
#define  MLX5_EVENT_TYPE_FPGA_QP_ERROR 151 
#define  MLX5_EVENT_TYPE_GENERAL_EVENT 150 
#define  MLX5_EVENT_TYPE_NIC_VPORT_CHANGE 149 
#define  MLX5_EVENT_TYPE_PAGE_REQUEST 148 
#define  MLX5_EVENT_TYPE_PATH_MIG 147 
#define  MLX5_EVENT_TYPE_PATH_MIG_FAILED 146 
#define  MLX5_EVENT_TYPE_PORT_CHANGE 145 
#define  MLX5_EVENT_TYPE_PORT_MODULE_EVENT 144 
#define  MLX5_EVENT_TYPE_PPS_EVENT 143 
#define  MLX5_EVENT_TYPE_SQ_DRAINED 142 
#define  MLX5_EVENT_TYPE_SRQ_CATAS_ERROR 141 
#define  MLX5_EVENT_TYPE_SRQ_LAST_WQE 140 
#define  MLX5_EVENT_TYPE_SRQ_RQ_LIMIT 139 
#define  MLX5_EVENT_TYPE_TEMP_WARN_EVENT 138 
#define  MLX5_EVENT_TYPE_WQ_ACCESS_ERROR 137 
#define  MLX5_EVENT_TYPE_WQ_CATAS_ERROR 136 
#define  MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR 135 
 int MLX5_NUM_SPARE_EQE ; 
#define  MLX5_PORT_CHANGE_SUBTYPE_ACTIVE 134 
#define  MLX5_PORT_CHANGE_SUBTYPE_CLIENT_REREG 133 
#define  MLX5_PORT_CHANGE_SUBTYPE_DOWN 132 
#define  MLX5_PORT_CHANGE_SUBTYPE_GUID 131 
#define  MLX5_PORT_CHANGE_SUBTYPE_INITIALIZED 130 
#define  MLX5_PORT_CHANGE_SUBTYPE_LID 129 
#define  MLX5_PORT_CHANGE_SUBTYPE_PKEY 128 
 int MLX5_RES_DCT ; 
 int MLX5_USER_INDEX_LEN ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  eq_update_ci (struct mlx5_eq*,int) ; 
 int eqe_type_str (int) ; 
 int /*<<< orphan*/  general_event_handler (struct mlx5_core_dev*,struct mlx5_eqe*) ; 
 int /*<<< orphan*/  mlx5_cmd_comp_handler (struct mlx5_core_dev*,int,int) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int,int,...) ; 
 int /*<<< orphan*/  mlx5_core_req_pages_handler (struct mlx5_core_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_eq_cq_completion (struct mlx5_eq*,int) ; 
 int /*<<< orphan*/  mlx5_eq_cq_event (struct mlx5_eq*,int,int) ; 
 int /*<<< orphan*/  mlx5_eswitch_vport_event (int /*<<< orphan*/ ,struct mlx5_eqe*) ; 
 int /*<<< orphan*/  mlx5_fpga_event (struct mlx5_core_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fw_tracer_event (struct mlx5_core_dev*,struct mlx5_eqe*) ; 
 int /*<<< orphan*/  mlx5_port_module_event (struct mlx5_core_dev*,struct mlx5_eqe*) ; 
 int /*<<< orphan*/  mlx5_pps_event (struct mlx5_core_dev*,struct mlx5_eqe*) ; 
 int /*<<< orphan*/  mlx5_rsc_event (struct mlx5_core_dev*,int,int) ; 
 int /*<<< orphan*/  mlx5_srq_event (struct mlx5_core_dev*,int,int) ; 
 int /*<<< orphan*/  mlx5_temp_warning_event (struct mlx5_core_dev*,struct mlx5_eqe*) ; 
 struct mlx5_eqe* next_eqe_sw (struct mlx5_eq*) ; 
 int /*<<< orphan*/  port_subtype_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mlx5_core_dev*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t mlx5_eq_int(int irq, void *eq_ptr)
{
	struct mlx5_eq *eq = eq_ptr;
	struct mlx5_core_dev *dev = eq->dev;
	struct mlx5_eqe *eqe;
	int set_ci = 0;
	u32 cqn = -1;
	u32 rsn;
	u8 port;

	while ((eqe = next_eqe_sw(eq))) {
		/*
		 * Make sure we read EQ entry contents after we've
		 * checked the ownership bit.
		 */
		dma_rmb();

		mlx5_core_dbg(eq->dev, "eqn %d, eqe type %s\n",
			      eq->eqn, eqe_type_str(eqe->type));
		switch (eqe->type) {
		case MLX5_EVENT_TYPE_COMP:
			cqn = be32_to_cpu(eqe->data.comp.cqn) & 0xffffff;
			mlx5_eq_cq_completion(eq, cqn);
			break;
		case MLX5_EVENT_TYPE_DCT_DRAINED:
			rsn = be32_to_cpu(eqe->data.dct.dctn) & 0xffffff;
			rsn |= (MLX5_RES_DCT << MLX5_USER_INDEX_LEN);
			mlx5_rsc_event(dev, rsn, eqe->type);
			break;
		case MLX5_EVENT_TYPE_PATH_MIG:
		case MLX5_EVENT_TYPE_COMM_EST:
		case MLX5_EVENT_TYPE_SQ_DRAINED:
		case MLX5_EVENT_TYPE_SRQ_LAST_WQE:
		case MLX5_EVENT_TYPE_WQ_CATAS_ERROR:
		case MLX5_EVENT_TYPE_PATH_MIG_FAILED:
		case MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
		case MLX5_EVENT_TYPE_WQ_ACCESS_ERROR:
			rsn = be32_to_cpu(eqe->data.qp_srq.qp_srq_n) & 0xffffff;
			rsn |= (eqe->data.qp_srq.type << MLX5_USER_INDEX_LEN);
			mlx5_core_dbg(dev, "event %s(%d) arrived on resource 0x%x\n",
				      eqe_type_str(eqe->type), eqe->type, rsn);
			mlx5_rsc_event(dev, rsn, eqe->type);
			break;

		case MLX5_EVENT_TYPE_SRQ_RQ_LIMIT:
		case MLX5_EVENT_TYPE_SRQ_CATAS_ERROR:
			rsn = be32_to_cpu(eqe->data.qp_srq.qp_srq_n) & 0xffffff;
			mlx5_core_dbg(dev, "SRQ event %s(%d): srqn 0x%x\n",
				      eqe_type_str(eqe->type), eqe->type, rsn);
			mlx5_srq_event(dev, rsn, eqe->type);
			break;

		case MLX5_EVENT_TYPE_CMD:
			mlx5_cmd_comp_handler(dev, be32_to_cpu(eqe->data.cmd.vector), false);
			break;

		case MLX5_EVENT_TYPE_PORT_CHANGE:
			port = (eqe->data.port.port >> 4) & 0xf;
			switch (eqe->sub_type) {
			case MLX5_PORT_CHANGE_SUBTYPE_DOWN:
			case MLX5_PORT_CHANGE_SUBTYPE_ACTIVE:
			case MLX5_PORT_CHANGE_SUBTYPE_LID:
			case MLX5_PORT_CHANGE_SUBTYPE_PKEY:
			case MLX5_PORT_CHANGE_SUBTYPE_GUID:
			case MLX5_PORT_CHANGE_SUBTYPE_CLIENT_REREG:
			case MLX5_PORT_CHANGE_SUBTYPE_INITIALIZED:
				if (dev->event)
					dev->event(dev, port_subtype_event(eqe->sub_type),
						   (unsigned long)port);
				break;
			default:
				mlx5_core_warn(dev, "Port event with unrecognized subtype: port %d, sub_type %d\n",
					       port, eqe->sub_type);
			}
			break;
		case MLX5_EVENT_TYPE_CQ_ERROR:
			cqn = be32_to_cpu(eqe->data.cq_err.cqn) & 0xffffff;
			mlx5_core_warn(dev, "CQ error on CQN 0x%x, syndrome 0x%x\n",
				       cqn, eqe->data.cq_err.syndrome);
			mlx5_eq_cq_event(eq, cqn, eqe->type);
			break;

		case MLX5_EVENT_TYPE_PAGE_REQUEST:
			{
				u16 func_id = be16_to_cpu(eqe->data.req_pages.func_id);
				s32 npages = be32_to_cpu(eqe->data.req_pages.num_pages);

				mlx5_core_dbg(dev, "page request for func 0x%x, npages %d\n",
					      func_id, npages);
				mlx5_core_req_pages_handler(dev, func_id, npages);
			}
			break;

		case MLX5_EVENT_TYPE_NIC_VPORT_CHANGE:
			mlx5_eswitch_vport_event(dev->priv.eswitch, eqe);
			break;

		case MLX5_EVENT_TYPE_PORT_MODULE_EVENT:
			mlx5_port_module_event(dev, eqe);
			break;

		case MLX5_EVENT_TYPE_PPS_EVENT:
			mlx5_pps_event(dev, eqe);
			break;

		case MLX5_EVENT_TYPE_FPGA_ERROR:
		case MLX5_EVENT_TYPE_FPGA_QP_ERROR:
			mlx5_fpga_event(dev, eqe->type, &eqe->data.raw);
			break;

		case MLX5_EVENT_TYPE_TEMP_WARN_EVENT:
			mlx5_temp_warning_event(dev, eqe);
			break;

		case MLX5_EVENT_TYPE_GENERAL_EVENT:
			general_event_handler(dev, eqe);
			break;

		case MLX5_EVENT_TYPE_DEVICE_TRACER:
			mlx5_fw_tracer_event(dev, eqe);
			break;

		default:
			mlx5_core_warn(dev, "Unhandled event 0x%x on EQ 0x%x\n",
				       eqe->type, eq->eqn);
			break;
		}

		++eq->cons_index;
		++set_ci;

		/* The HCA will think the queue has overflowed if we
		 * don't tell it we've been processing events.  We
		 * create our EQs with MLX5_NUM_SPARE_EQE extra
		 * entries, so we must update our consumer index at
		 * least that often.
		 */
		if (unlikely(set_ci >= MLX5_NUM_SPARE_EQE)) {
			eq_update_ci(eq, 0);
			set_ci = 0;
		}
	}

	eq_update_ci(eq, 1);

	if (cqn != -1)
		tasklet_schedule(&eq->tasklet_ctx.task);

	return IRQ_HANDLED;
}