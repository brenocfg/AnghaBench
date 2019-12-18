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
struct TYPE_5__ {int param1; int /*<<< orphan*/  cmd; } ;
union octnet_cmd {TYPE_1__ s; scalar_t__ u64; } ;
typedef  int /*<<< orphan*/  u64 ;
struct octeon_soft_command {int /*<<< orphan*/  caller_is_done; scalar_t__ sc_status; int /*<<< orphan*/  iq_no; int /*<<< orphan*/  complete; scalar_t__ virtdptr; } ;
struct octeon_device {int dummy; } ;
struct net_device {int mtu; } ;
struct TYPE_8__ {TYPE_3__* txpciq; } ;
struct lio {int mtu; int /*<<< orphan*/  netdev; TYPE_4__ linfo; struct octeon_device* oct_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_7__ {TYPE_2__ s; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int IQ_SEND_FAILED ; 
 scalar_t__ OCTEON_REQUEST_PENDING ; 
 int /*<<< orphan*/  OCTNET_CMD_CHANGE_MTU ; 
 int OCTNET_CMD_SIZE ; 
 int /*<<< orphan*/  OPCODE_NIC ; 
 int /*<<< orphan*/  OPCODE_NIC_CMD ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_info (struct lio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ octeon_alloc_soft_command (struct octeon_device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_free_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_prepare_soft_command (struct octeon_device*,struct octeon_soft_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int octeon_send_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_swap_8B_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rx_err ; 
 int wait_for_sc_completion_timeout (struct octeon_device*,struct octeon_soft_command*,int /*<<< orphan*/ ) ; 

int liquidio_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;
	struct octeon_soft_command *sc;
	union octnet_cmd *ncmd;
	int ret = 0;

	sc = (struct octeon_soft_command *)
		octeon_alloc_soft_command(oct, OCTNET_CMD_SIZE, 16, 0);
	if (!sc) {
		netif_info(lio, rx_err, lio->netdev,
			   "Failed to allocate soft command\n");
		return -ENOMEM;
	}

	ncmd = (union octnet_cmd *)sc->virtdptr;

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	ncmd->u64 = 0;
	ncmd->s.cmd = OCTNET_CMD_CHANGE_MTU;
	ncmd->s.param1 = new_mtu;

	octeon_swap_8B_data((u64 *)ncmd, (OCTNET_CMD_SIZE >> 3));

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	octeon_prepare_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_CMD, 0, 0, 0);

	ret = octeon_send_soft_command(oct, sc);
	if (ret == IQ_SEND_FAILED) {
		netif_info(lio, rx_err, lio->netdev, "Failed to change MTU\n");
		octeon_free_soft_command(oct, sc);
		return -EINVAL;
	}
	/* Sleep on a wait queue till the cond flag indicates that the
	 * response arrived or timed-out.
	 */
	ret = wait_for_sc_completion_timeout(oct, sc, 0);
	if (ret)
		return ret;

	if (sc->sc_status) {
		WRITE_ONCE(sc->caller_is_done, true);
		return -EINVAL;
	}

	netdev->mtu = new_mtu;
	lio->mtu = new_mtu;

	WRITE_ONCE(sc->caller_is_done, true);
	return 0;
}