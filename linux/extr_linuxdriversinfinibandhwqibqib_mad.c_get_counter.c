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
typedef  int /*<<< orphan*/  u64 ;
struct qib_pportdata {TYPE_1__* dd; } ;
struct qib_ibport {int dummy; } ;
typedef  int __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* f_portcntr ) (struct qib_pportdata*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  IB_PMA_PORT_RCV_DATA 132 
#define  IB_PMA_PORT_RCV_PKTS 131 
#define  IB_PMA_PORT_XMIT_DATA 130 
#define  IB_PMA_PORT_XMIT_PKTS 129 
#define  IB_PMA_PORT_XMIT_WAIT 128 
 int /*<<< orphan*/  QIBPORTCNTR_PSRCVDATA ; 
 int /*<<< orphan*/  QIBPORTCNTR_PSRCVPKTS ; 
 int /*<<< orphan*/  QIBPORTCNTR_PSXMITDATA ; 
 int /*<<< orphan*/  QIBPORTCNTR_PSXMITPKTS ; 
 int /*<<< orphan*/  QIBPORTCNTR_PSXMITWAIT ; 
 int /*<<< orphan*/  stub1 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 get_counter(struct qib_ibport *ibp, struct qib_pportdata *ppd,
		       __be16 sel)
{
	u64 ret;

	switch (sel) {
	case IB_PMA_PORT_XMIT_DATA:
		ret = ppd->dd->f_portcntr(ppd, QIBPORTCNTR_PSXMITDATA);
		break;
	case IB_PMA_PORT_RCV_DATA:
		ret = ppd->dd->f_portcntr(ppd, QIBPORTCNTR_PSRCVDATA);
		break;
	case IB_PMA_PORT_XMIT_PKTS:
		ret = ppd->dd->f_portcntr(ppd, QIBPORTCNTR_PSXMITPKTS);
		break;
	case IB_PMA_PORT_RCV_PKTS:
		ret = ppd->dd->f_portcntr(ppd, QIBPORTCNTR_PSRCVPKTS);
		break;
	case IB_PMA_PORT_XMIT_WAIT:
		ret = ppd->dd->f_portcntr(ppd, QIBPORTCNTR_PSXMITWAIT);
		break;
	default:
		ret = 0;
	}

	return ret;
}