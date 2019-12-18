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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct opa_smp {int /*<<< orphan*/  status; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_device {int dummy; } ;
struct hfi1_devdata {TYPE_1__* pport; } ;
struct TYPE_2__ {scalar_t__ port_type; } ;

/* Variables and functions */
 int ENODEV ; 
 int ERANGE ; 
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int /*<<< orphan*/  IB_SMP_UNSUP_METH_ATTR ; 
 int OPA_AM_CI_ADDR (int) ; 
 int OPA_AM_CI_LEN (int) ; 
 scalar_t__ PORT_TYPE_QSFP ; 
 scalar_t__ __CI_PAGE_NUM (int) ; 
 struct hfi1_devdata* dd_from_ibdev (struct ib_device*) ; 
 int get_cable_info (struct hfi1_devdata*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int reply (struct ib_mad_hdr*) ; 
 scalar_t__ smp_length_check (int,int) ; 

__attribute__((used)) static int __subn_get_opa_cable_info(struct opa_smp *smp, u32 am, u8 *data,
				     struct ib_device *ibdev, u8 port,
				     u32 *resp_len, u32 max_len)
{
	struct hfi1_devdata *dd = dd_from_ibdev(ibdev);
	u32 addr = OPA_AM_CI_ADDR(am);
	u32 len = OPA_AM_CI_LEN(am) + 1;
	int ret;

	if (dd->pport->port_type != PORT_TYPE_QSFP ||
	    smp_length_check(len, max_len)) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

#define __CI_PAGE_SIZE BIT(7) /* 128 bytes */
#define __CI_PAGE_MASK ~(__CI_PAGE_SIZE - 1)
#define __CI_PAGE_NUM(a) ((a) & __CI_PAGE_MASK)

	/*
	 * check that addr is within spec, and
	 * addr and (addr + len - 1) are on the same "page"
	 */
	if (addr >= 4096 ||
	    (__CI_PAGE_NUM(addr) != __CI_PAGE_NUM(addr + len - 1))) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	ret = get_cable_info(dd, port, addr, len, data);

	if (ret == -ENODEV) {
		smp->status |= IB_SMP_UNSUP_METH_ATTR;
		return reply((struct ib_mad_hdr *)smp);
	}

	/* The address range for the CableInfo SMA query is wider than the
	 * memory available on the QSFP cable. We want to return a valid
	 * response, albeit zeroed out, for address ranges beyond available
	 * memory but that are within the CableInfo query spec
	 */
	if (ret < 0 && ret != -ERANGE) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	if (resp_len)
		*resp_len += len;

	return reply((struct ib_mad_hdr *)smp);
}