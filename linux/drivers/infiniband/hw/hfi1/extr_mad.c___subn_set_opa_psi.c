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
typedef  int u8 ;
typedef  int u32 ;
struct opa_smp {int /*<<< orphan*/  status; } ;
struct opa_port_state_info {int /*<<< orphan*/  port_states; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_device {int dummy; } ;
struct hfi1_pportdata {int is_sm_config_started; } ;
struct hfi1_ibport {int dummy; } ;

/* Variables and functions */
 int IB_PORT_ARMED ; 
 int IB_PORT_INIT ; 
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int OPA_AM_NPORT (int) ; 
 int OPA_AM_START_SM_CFG (int) ; 
 int __subn_get_opa_psi (struct opa_smp*,int,int*,struct ib_device*,int,int*,int) ; 
 int driver_lstate (struct hfi1_pportdata*) ; 
 int port_states_to_logical_state (int /*<<< orphan*/ *) ; 
 int port_states_to_phys_state (int /*<<< orphan*/ *) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 int reply (struct ib_mad_hdr*) ; 
 int set_port_states (struct hfi1_pportdata*,struct opa_smp*,int,int,int) ; 
 scalar_t__ smp_length_check (int,int) ; 
 struct hfi1_ibport* to_iport (struct ib_device*,int) ; 

__attribute__((used)) static int __subn_set_opa_psi(struct opa_smp *smp, u32 am, u8 *data,
			      struct ib_device *ibdev, u8 port,
			      u32 *resp_len, u32 max_len, int local_mad)
{
	u32 nports = OPA_AM_NPORT(am);
	u32 start_of_sm_config = OPA_AM_START_SM_CFG(am);
	u32 ls_old;
	u8 ls_new, ps_new;
	struct hfi1_ibport *ibp;
	struct hfi1_pportdata *ppd;
	struct opa_port_state_info *psi = (struct opa_port_state_info *)data;
	int ret, invalid = 0;

	if (nports != 1 || smp_length_check(sizeof(*psi), max_len)) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	ibp = to_iport(ibdev, port);
	ppd = ppd_from_ibp(ibp);

	ls_old = driver_lstate(ppd);

	ls_new = port_states_to_logical_state(&psi->port_states);
	ps_new = port_states_to_phys_state(&psi->port_states);

	if (ls_old == IB_PORT_INIT) {
		if (start_of_sm_config) {
			if (ls_new == ls_old || (ls_new == IB_PORT_ARMED))
				ppd->is_sm_config_started = 1;
		} else if (ls_new == IB_PORT_ARMED) {
			if (ppd->is_sm_config_started == 0) {
				invalid = 1;
				smp->status |= IB_SMP_INVALID_FIELD;
			}
		}
	}

	if (!invalid) {
		ret = set_port_states(ppd, smp, ls_new, ps_new, local_mad);
		if (ret)
			return ret;
	}

	return __subn_get_opa_psi(smp, am, data, ibdev, port, resp_len,
				  max_len);
}