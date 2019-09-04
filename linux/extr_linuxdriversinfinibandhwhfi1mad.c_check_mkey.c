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
struct ib_mad_hdr {int method; } ;
struct TYPE_2__ {int mkey_lease_timeout; int mkeyprot; scalar_t__ mkey; int mkey_violations; int mkey_lease_period; } ;
struct hfi1_ibport {TYPE_1__ rvp; } ;
typedef  scalar_t__ __be64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int HZ ; 
 int IB_MAD_IGNORE_MKEY ; 
#define  IB_MGMT_METHOD_GET 130 
#define  IB_MGMT_METHOD_SET 129 
#define  IB_MGMT_METHOD_TRAP_REPRESS 128 
 int /*<<< orphan*/  bad_mkey (struct hfi1_ibport*,struct ib_mad_hdr*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int jiffies ; 
 scalar_t__ time_after_eq (int,int) ; 

__attribute__((used)) static int check_mkey(struct hfi1_ibport *ibp, struct ib_mad_hdr *mad,
		      int mad_flags, __be64 mkey, __be32 dr_slid,
		      u8 return_path[], u8 hop_cnt)
{
	int valid_mkey = 0;
	int ret = 0;

	/* Is the mkey in the process of expiring? */
	if (ibp->rvp.mkey_lease_timeout &&
	    time_after_eq(jiffies, ibp->rvp.mkey_lease_timeout)) {
		/* Clear timeout and mkey protection field. */
		ibp->rvp.mkey_lease_timeout = 0;
		ibp->rvp.mkeyprot = 0;
	}

	if ((mad_flags & IB_MAD_IGNORE_MKEY) ||  ibp->rvp.mkey == 0 ||
	    ibp->rvp.mkey == mkey)
		valid_mkey = 1;

	/* Unset lease timeout on any valid Get/Set/TrapRepress */
	if (valid_mkey && ibp->rvp.mkey_lease_timeout &&
	    (mad->method == IB_MGMT_METHOD_GET ||
	     mad->method == IB_MGMT_METHOD_SET ||
	     mad->method == IB_MGMT_METHOD_TRAP_REPRESS))
		ibp->rvp.mkey_lease_timeout = 0;

	if (!valid_mkey) {
		switch (mad->method) {
		case IB_MGMT_METHOD_GET:
			/* Bad mkey not a violation below level 2 */
			if (ibp->rvp.mkeyprot < 2)
				break;
			/* fall through */
		case IB_MGMT_METHOD_SET:
		case IB_MGMT_METHOD_TRAP_REPRESS:
			if (ibp->rvp.mkey_violations != 0xFFFF)
				++ibp->rvp.mkey_violations;
			if (!ibp->rvp.mkey_lease_timeout &&
			    ibp->rvp.mkey_lease_period)
				ibp->rvp.mkey_lease_timeout = jiffies +
					ibp->rvp.mkey_lease_period * HZ;
			/* Generate a trap notice. */
			bad_mkey(ibp, mad, mkey, dr_slid, return_path,
				 hop_cnt);
			ret = 1;
		}
	}

	return ret;
}