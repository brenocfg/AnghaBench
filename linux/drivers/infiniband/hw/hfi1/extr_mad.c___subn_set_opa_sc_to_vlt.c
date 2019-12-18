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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct opa_smp {int /*<<< orphan*/  status; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_device {int dummy; } ;
struct hfi1_pportdata {int dummy; } ;
struct hfi1_devdata {struct hfi1_pportdata* pport; } ;

/* Variables and functions */
 int IB_PORT_ACTIVE ; 
 int IB_PORT_ARMED ; 
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int OPA_AM_ASYNC (int) ; 
 int OPA_AM_NBLK (int) ; 
 int __subn_get_opa_sc_to_vlt (struct opa_smp*,int,int*,struct ib_device*,int,int*,int) ; 
 struct hfi1_devdata* dd_from_ibdev (struct ib_device*) ; 
 int driver_lstate (struct hfi1_pportdata*) ; 
 int reply (struct ib_mad_hdr*) ; 
 int /*<<< orphan*/  set_sc2vlt_tables (struct hfi1_devdata*,void*) ; 
 scalar_t__ smp_length_check (size_t,int) ; 

__attribute__((used)) static int __subn_set_opa_sc_to_vlt(struct opa_smp *smp, u32 am, u8 *data,
				    struct ib_device *ibdev, u8 port,
				    u32 *resp_len, u32 max_len)
{
	u32 n_blocks = OPA_AM_NBLK(am);
	int async_update = OPA_AM_ASYNC(am);
	struct hfi1_devdata *dd = dd_from_ibdev(ibdev);
	void *vp = (void *)data;
	struct hfi1_pportdata *ppd;
	int lstate;
	/*
	 * set_sc2vlt_tables writes the information contained in *data
	 * to four 64-bit registers SendSC2VLt[0-3]. We need to make
	 * sure *max_len is not greater than the total size of the four
	 * SendSC2VLt[0-3] registers.
	 */
	size_t size = 4 * sizeof(u64);

	if (n_blocks != 1 || async_update || smp_length_check(size, max_len)) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	/* IB numbers ports from 1, hw from 0 */
	ppd = dd->pport + (port - 1);
	lstate = driver_lstate(ppd);
	/*
	 * it's known that async_update is 0 by this point, but include
	 * the explicit check for clarity
	 */
	if (!async_update &&
	    (lstate == IB_PORT_ARMED || lstate == IB_PORT_ACTIVE)) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	set_sc2vlt_tables(dd, vp);

	return __subn_get_opa_sc_to_vlt(smp, am, data, ibdev, port, resp_len,
					max_len);
}