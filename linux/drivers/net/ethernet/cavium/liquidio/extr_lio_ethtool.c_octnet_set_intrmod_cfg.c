#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct octeon_soft_command {int sc_status; int /*<<< orphan*/  caller_is_done; int /*<<< orphan*/  complete; int /*<<< orphan*/  iq_no; scalar_t__ virtdptr; } ;
struct octeon_device {TYPE_4__* pci_dev; } ;
struct oct_intrmod_cfg {scalar_t__ rx_enable; } ;
struct TYPE_7__ {TYPE_2__* txpciq; } ;
struct lio {TYPE_3__ linfo; struct octeon_device* oct_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_6__ {TYPE_1__ s; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int IQ_SEND_FAILED ; 
 int OCTEON_REQUEST_PENDING ; 
 int /*<<< orphan*/  OPCODE_NIC ; 
 int /*<<< orphan*/  OPCODE_NIC_INTRMOD_CFG ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct oct_intrmod_cfg*,struct oct_intrmod_cfg*,int) ; 
 scalar_t__ octeon_alloc_soft_command (struct octeon_device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_free_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_prepare_soft_command (struct octeon_device*,struct octeon_soft_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int octeon_send_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_swap_8B_data (int /*<<< orphan*/ *,int) ; 
 int wait_for_sc_completion_timeout (struct octeon_device*,struct octeon_soft_command*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int octnet_set_intrmod_cfg(struct lio *lio,
				  struct oct_intrmod_cfg *intr_cfg)
{
	struct octeon_soft_command *sc;
	struct oct_intrmod_cfg *cfg;
	int retval;
	struct octeon_device *oct_dev = lio->oct_dev;

	/* Alloc soft command */
	sc = (struct octeon_soft_command *)
		octeon_alloc_soft_command(oct_dev,
					  sizeof(struct oct_intrmod_cfg),
					  16, 0);

	if (!sc)
		return -ENOMEM;

	cfg = (struct oct_intrmod_cfg *)sc->virtdptr;

	memcpy(cfg, intr_cfg, sizeof(struct oct_intrmod_cfg));
	octeon_swap_8B_data((u64 *)cfg, (sizeof(struct oct_intrmod_cfg)) / 8);

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	octeon_prepare_soft_command(oct_dev, sc, OPCODE_NIC,
				    OPCODE_NIC_INTRMOD_CFG, 0, 0, 0);

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	retval = octeon_send_soft_command(oct_dev, sc);
	if (retval == IQ_SEND_FAILED) {
		octeon_free_soft_command(oct_dev, sc);
		return -EINVAL;
	}

	/* Sleep on a wait queue till the cond flag indicates that the
	 * response arrived or timed-out.
	 */
	retval = wait_for_sc_completion_timeout(oct_dev, sc, 0);
	if (retval)
		return retval;

	retval = sc->sc_status;
	if (retval == 0) {
		dev_info(&oct_dev->pci_dev->dev,
			 "Rx-Adaptive Interrupt moderation %s\n",
			 (intr_cfg->rx_enable) ?
			 "enabled" : "disabled");
		WRITE_ONCE(sc->caller_is_done, true);
		return 0;
	}

	dev_err(&oct_dev->pci_dev->dev,
		"intrmod config failed. Status: %x\n", retval);
	WRITE_ONCE(sc->caller_is_done, true);
	return -ENODEV;
}