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
struct ib_mad_hdr {int dummy; } ;
struct ib_device {int dummy; } ;
struct hfi1_pportdata {int dummy; } ;
struct hfi1_devdata {struct hfi1_pportdata* pport; } ;
struct buffer_control {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_TBL_BUFFER_CONTROL ; 
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int OPA_AM_NPORT (int) ; 
 int __subn_get_opa_bct (struct opa_smp*,int,int*,struct ib_device*,int,int*,int) ; 
 struct hfi1_devdata* dd_from_ibdev (struct ib_device*) ; 
 scalar_t__ fm_set_table (struct hfi1_pportdata*,int /*<<< orphan*/ ,struct buffer_control*) ; 
 int reply (struct ib_mad_hdr*) ; 
 scalar_t__ smp_length_check (int,int) ; 
 int /*<<< orphan*/  trace_bct_set (struct hfi1_devdata*,struct buffer_control*) ; 

__attribute__((used)) static int __subn_set_opa_bct(struct opa_smp *smp, u32 am, u8 *data,
			      struct ib_device *ibdev, u8 port, u32 *resp_len,
			      u32 max_len)
{
	u32 num_ports = OPA_AM_NPORT(am);
	struct hfi1_devdata *dd = dd_from_ibdev(ibdev);
	struct hfi1_pportdata *ppd;
	struct buffer_control *p = (struct buffer_control *)data;

	if (num_ports != 1 || smp_length_check(sizeof(*p), max_len)) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}
	ppd = dd->pport + (port - 1);
	trace_bct_set(dd, p);
	if (fm_set_table(ppd, FM_TBL_BUFFER_CONTROL, p) < 0) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	return __subn_get_opa_bct(smp, am, data, ibdev, port, resp_len,
				  max_len);
}