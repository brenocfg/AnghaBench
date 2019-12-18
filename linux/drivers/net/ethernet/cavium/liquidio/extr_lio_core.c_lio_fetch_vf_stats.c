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
struct octeon_soft_command {scalar_t__ sc_status; int /*<<< orphan*/  caller_is_done; int /*<<< orphan*/  iq_no; int /*<<< orphan*/  complete; scalar_t__ virtrptr; } ;
struct octeon_device {TYPE_4__* pci_dev; } ;
struct oct_nic_vf_stats_resp {scalar_t__ spoofmac_cnt; int /*<<< orphan*/  status; } ;
struct TYPE_7__ {TYPE_2__* txpciq; } ;
struct lio {TYPE_3__ linfo; struct octeon_device* oct_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_6__ {TYPE_1__ s; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IQ_SEND_FAILED ; 
 int LIO_SC_MAX_TMO_MS ; 
 scalar_t__ OCTEON_REQUEST_PENDING ; 
 scalar_t__ OCTEON_REQUEST_TIMEOUT ; 
 int /*<<< orphan*/  OPCODE_NIC ; 
 int /*<<< orphan*/  OPCODE_NIC_VF_PORT_STATS ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct oct_nic_vf_stats_resp*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ octeon_alloc_soft_command (struct octeon_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_free_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_prepare_soft_command (struct octeon_device*,struct octeon_soft_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int octeon_send_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_swap_8B_data (int /*<<< orphan*/ *,int) ; 
 int wait_for_sc_completion_timeout (struct octeon_device*,struct octeon_soft_command*,int) ; 

__attribute__((used)) static int lio_fetch_vf_stats(struct lio *lio)
{
	struct octeon_device *oct_dev = lio->oct_dev;
	struct octeon_soft_command *sc;
	struct oct_nic_vf_stats_resp *resp;

	int retval;

	/* Alloc soft command */
	sc = (struct octeon_soft_command *)
		octeon_alloc_soft_command(oct_dev,
					  0,
					  sizeof(struct oct_nic_vf_stats_resp),
					  0);

	if (!sc) {
		dev_err(&oct_dev->pci_dev->dev, "Soft command allocation failed\n");
		retval = -ENOMEM;
		goto lio_fetch_vf_stats_exit;
	}

	resp = (struct oct_nic_vf_stats_resp *)sc->virtrptr;
	memset(resp, 0, sizeof(struct oct_nic_vf_stats_resp));

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	octeon_prepare_soft_command(oct_dev, sc, OPCODE_NIC,
				    OPCODE_NIC_VF_PORT_STATS, 0, 0, 0);

	retval = octeon_send_soft_command(oct_dev, sc);
	if (retval == IQ_SEND_FAILED) {
		octeon_free_soft_command(oct_dev, sc);
		goto lio_fetch_vf_stats_exit;
	}

	retval =
		wait_for_sc_completion_timeout(oct_dev, sc,
					       (2 * LIO_SC_MAX_TMO_MS));
	if (retval)  {
		dev_err(&oct_dev->pci_dev->dev,
			"sc OPCODE_NIC_VF_PORT_STATS command failed\n");
		goto lio_fetch_vf_stats_exit;
	}

	if (sc->sc_status != OCTEON_REQUEST_TIMEOUT && !resp->status) {
		octeon_swap_8B_data((u64 *)&resp->spoofmac_cnt,
				    (sizeof(u64)) >> 3);

		if (resp->spoofmac_cnt != 0) {
			dev_warn(&oct_dev->pci_dev->dev,
				 "%llu Spoofed packets detected\n",
				 resp->spoofmac_cnt);
		}
	}
	WRITE_ONCE(sc->caller_is_done, 1);

lio_fetch_vf_stats_exit:
	return retval;
}