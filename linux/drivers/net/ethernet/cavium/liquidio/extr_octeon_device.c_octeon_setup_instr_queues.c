#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ qpg; scalar_t__ use_qpg; int /*<<< orphan*/  pkind; int /*<<< orphan*/  q_no; } ;
union oct_txpciq {TYPE_3__ s; scalar_t__ u64; } ;
typedef  int /*<<< orphan*/  u32 ;
struct octeon_instr_queue {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  pkind; } ;
struct octeon_device {scalar_t__ num_iqs; TYPE_4__** instr_queue; TYPE_2__ pfvf_hsword; TYPE_1__* pci_dev; } ;
struct TYPE_11__ {scalar_t__ ifidx; void* app_ctx; scalar_t__ q_index; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_GET_NUM_DEF_TX_DESCS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIP_CONF (struct octeon_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ OCTEON_CN23XX_PF (struct octeon_device*) ; 
 scalar_t__ OCTEON_CN23XX_VF (struct octeon_device*) ; 
 scalar_t__ OCTEON_CN6XXX (struct octeon_device*) ; 
 int /*<<< orphan*/  cn23xx_pf ; 
 int /*<<< orphan*/  cn23xx_vf ; 
 int /*<<< orphan*/  cn6xxx ; 
 int dev_to_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ octeon_init_instr_queue (struct octeon_device*,union oct_txpciq,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (TYPE_4__*) ; 
 TYPE_4__* vzalloc (int) ; 
 TYPE_4__* vzalloc_node (int,int) ; 

int octeon_setup_instr_queues(struct octeon_device *oct)
{
	u32 num_descs = 0;
	u32 iq_no = 0;
	union oct_txpciq txpciq;
	int numa_node = dev_to_node(&oct->pci_dev->dev);

	if (OCTEON_CN6XXX(oct))
		num_descs =
			CFG_GET_NUM_DEF_TX_DESCS(CHIP_CONF(oct, cn6xxx));
	else if (OCTEON_CN23XX_PF(oct))
		num_descs = CFG_GET_NUM_DEF_TX_DESCS(CHIP_CONF(oct, cn23xx_pf));
	else if (OCTEON_CN23XX_VF(oct))
		num_descs = CFG_GET_NUM_DEF_TX_DESCS(CHIP_CONF(oct, cn23xx_vf));

	oct->num_iqs = 0;

	oct->instr_queue[0] = vzalloc_node(sizeof(*oct->instr_queue[0]),
				numa_node);
	if (!oct->instr_queue[0])
		oct->instr_queue[0] =
			vzalloc(sizeof(struct octeon_instr_queue));
	if (!oct->instr_queue[0])
		return 1;
	memset(oct->instr_queue[0], 0, sizeof(struct octeon_instr_queue));
	oct->instr_queue[0]->q_index = 0;
	oct->instr_queue[0]->app_ctx = (void *)(size_t)0;
	oct->instr_queue[0]->ifidx = 0;
	txpciq.u64 = 0;
	txpciq.s.q_no = iq_no;
	txpciq.s.pkind = oct->pfvf_hsword.pkind;
	txpciq.s.use_qpg = 0;
	txpciq.s.qpg = 0;
	if (octeon_init_instr_queue(oct, txpciq, num_descs)) {
		/* prevent memory leak */
		vfree(oct->instr_queue[0]);
		oct->instr_queue[0] = NULL;
		return 1;
	}

	oct->num_iqs++;
	return 0;
}