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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct octeon_soft_command {int /*<<< orphan*/  caller_is_done; int /*<<< orphan*/  sc_status; int /*<<< orphan*/  complete; int /*<<< orphan*/  iq_no; } ;
struct octeon_device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* txpciq; } ;
struct lio {TYPE_3__ linfo; struct octeon_device* oct_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_5__ {TYPE_1__ s; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IQ_SEND_FAILED ; 
 int /*<<< orphan*/  OCTEON_REQUEST_PENDING ; 
 int /*<<< orphan*/  OPCODE_NIC ; 
 int /*<<< orphan*/  OPCODE_NIC_SET_TRUSTED_VF ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct octeon_soft_command* octeon_alloc_soft_command (struct octeon_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_free_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_prepare_soft_command (struct octeon_device*,struct octeon_soft_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int octeon_send_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int wait_for_sc_completion_timeout (struct octeon_device*,struct octeon_soft_command*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int liquidio_send_vf_trust_cmd(struct lio *lio, int vfidx, bool trusted)
{
	struct octeon_device *oct = lio->oct_dev;
	struct octeon_soft_command *sc;
	int retval;

	sc = octeon_alloc_soft_command(oct, 0, 16, 0);
	if (!sc)
		return -ENOMEM;

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	/* vfidx is 0 based, but vf_num (param1) is 1 based */
	octeon_prepare_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_SET_TRUSTED_VF, 0, vfidx + 1,
				    trusted);

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	retval = octeon_send_soft_command(oct, sc);
	if (retval == IQ_SEND_FAILED) {
		octeon_free_soft_command(oct, sc);
		retval = -1;
	} else {
		/* Wait for response or timeout */
		retval = wait_for_sc_completion_timeout(oct, sc, 0);
		if (retval)
			return (retval);

		WRITE_ONCE(sc->caller_is_done, true);
	}

	return retval;
}