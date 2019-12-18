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
typedef  int u32 ;
struct TYPE_2__ {int class; } ;
struct sched_queue_entry {int /*<<< orphan*/  cntxt_id; TYPE_1__ param; } ;
struct port_info {struct adapter* adapter; } ;
struct adapter {unsigned int pf; int /*<<< orphan*/  mbox; } ;
typedef  enum sched_bind_type { ____Placeholder_sched_bind_type } sched_bind_type ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  FW_PARAMS_MNEM_DMAQ ; 
 int FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DMAQ_EQ_SCHEDCLASS_ETH ; 
 int FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 int FW_PARAMS_PARAM_YZ_V (int /*<<< orphan*/ ) ; 
 int FW_SCHED_CLS_NONE ; 
#define  SCHED_QUEUE 128 
 int t4_set_params (struct adapter*,int /*<<< orphan*/ ,unsigned int,unsigned int,int,int*,int*) ; 

__attribute__((used)) static int t4_sched_bind_unbind_op(struct port_info *pi, void *arg,
				   enum sched_bind_type type, bool bind)
{
	struct adapter *adap = pi->adapter;
	u32 fw_mnem, fw_class, fw_param;
	unsigned int pf = adap->pf;
	unsigned int vf = 0;
	int err = 0;

	switch (type) {
	case SCHED_QUEUE: {
		struct sched_queue_entry *qe;

		qe = (struct sched_queue_entry *)arg;

		/* Create a template for the FW_PARAMS_CMD mnemonic and
		 * value (TX Scheduling Class in this case).
		 */
		fw_mnem = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DMAQ) |
			   FW_PARAMS_PARAM_X_V(
				   FW_PARAMS_PARAM_DMAQ_EQ_SCHEDCLASS_ETH));
		fw_class = bind ? qe->param.class : FW_SCHED_CLS_NONE;
		fw_param = (fw_mnem | FW_PARAMS_PARAM_YZ_V(qe->cntxt_id));

		pf = adap->pf;
		vf = 0;
		break;
	}
	default:
		err = -ENOTSUPP;
		goto out;
	}

	err = t4_set_params(adap, adap->mbox, pf, vf, 1, &fw_param, &fw_class);

out:
	return err;
}