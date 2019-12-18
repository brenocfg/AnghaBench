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
typedef  int u64 ;
typedef  scalar_t__ u16 ;
struct hfi1_devdata {int dummy; } ;
struct hfi1_ctxtdata {TYPE_1__* sc; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_context; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SEND_CTXT_CHECK_ENABLE ; 
 int SEND_CTXT_CHECK_ENABLE_CHECK_PARTITION_KEY_SMASK ; 
 int SEND_CTXT_CHECK_ENABLE_DISALLOW_KDETH_PACKETS_SMASK ; 
 int /*<<< orphan*/  SEND_CTXT_CHECK_PARTITION_KEY ; 
 int SEND_CTXT_CHECK_PARTITION_KEY_VALUE_MASK ; 
 int SEND_CTXT_CHECK_PARTITION_KEY_VALUE_SHIFT ; 
 int read_kctxt_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_kctxt_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int hfi1_set_ctxt_pkey(struct hfi1_devdata *dd, struct hfi1_ctxtdata *rcd,
		       u16 pkey)
{
	u8 hw_ctxt;
	u64 reg;

	if (!rcd || !rcd->sc)
		return -EINVAL;

	hw_ctxt = rcd->sc->hw_context;
	reg = ((u64)pkey & SEND_CTXT_CHECK_PARTITION_KEY_VALUE_MASK) <<
		SEND_CTXT_CHECK_PARTITION_KEY_VALUE_SHIFT;
	write_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_PARTITION_KEY, reg);
	reg = read_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_ENABLE);
	reg |= SEND_CTXT_CHECK_ENABLE_CHECK_PARTITION_KEY_SMASK;
	reg &= ~SEND_CTXT_CHECK_ENABLE_DISALLOW_KDETH_PACKETS_SMASK;
	write_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_ENABLE, reg);

	return 0;
}