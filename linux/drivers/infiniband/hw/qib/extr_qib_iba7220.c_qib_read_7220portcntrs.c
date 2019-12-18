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
typedef  size_t u32 ;
struct qib_pportdata {int dummy; } ;
struct qib_devdata {TYPE_1__* cspec; struct qib_pportdata* pport; } ;
typedef  size_t loff_t ;
struct TYPE_2__ {size_t portcntrnamelen; int nportcntrs; int /*<<< orphan*/ * portcntrs; } ;

/* Variables and functions */
 int _PORT_VIRT_FLAG ; 
 int* portcntr7220indices ; 
 scalar_t__ portcntr7220names ; 
 int /*<<< orphan*/  qib_portcntr_7220 (struct qib_pportdata*,int) ; 
 int /*<<< orphan*/  read_7220_creg32 (struct qib_devdata*,int) ; 

__attribute__((used)) static u32 qib_read_7220portcntrs(struct qib_devdata *dd, loff_t pos, u32 port,
				  char **namep, u64 **cntrp)
{
	u32 ret;

	if (!dd->cspec->portcntrs) {
		ret = 0;
		goto done;
	}
	if (namep) {
		*namep = (char *)portcntr7220names;
		ret = dd->cspec->portcntrnamelen;
		if (pos >= ret)
			ret = 0; /* final read after getting everything */
	} else {
		u64 *cntr = dd->cspec->portcntrs;
		struct qib_pportdata *ppd = &dd->pport[port];
		int i;

		ret = dd->cspec->nportcntrs * sizeof(u64);
		if (!cntr || pos >= ret) {
			/* everything read, or couldn't get memory */
			ret = 0;
			goto done;
		}
		*cntrp = cntr;
		for (i = 0; i < dd->cspec->nportcntrs; i++) {
			if (portcntr7220indices[i] & _PORT_VIRT_FLAG)
				*cntr++ = qib_portcntr_7220(ppd,
					portcntr7220indices[i] &
					~_PORT_VIRT_FLAG);
			else
				*cntr++ = read_7220_creg32(dd,
					   portcntr7220indices[i]);
		}
	}
done:
	return ret;
}