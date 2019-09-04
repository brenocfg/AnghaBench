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
typedef  scalar_t__ u32 ;
struct qib_devdata {TYPE_1__* cspec; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {scalar_t__ cntrnamelen; int ncntrs; int /*<<< orphan*/ * cntrs; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cntr6120indices ; 
 scalar_t__ cntr6120names ; 
 int /*<<< orphan*/  read_6120_creg32 (struct qib_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 qib_read_6120cntrs(struct qib_devdata *dd, loff_t pos, char **namep,
			      u64 **cntrp)
{
	u32 ret;

	if (namep) {
		ret = dd->cspec->cntrnamelen;
		if (pos >= ret)
			ret = 0; /* final read after getting everything */
		else
			*namep = (char *)cntr6120names;
	} else {
		u64 *cntr = dd->cspec->cntrs;
		int i;

		ret = dd->cspec->ncntrs * sizeof(u64);
		if (!cntr || pos >= ret) {
			/* everything read, or couldn't get memory */
			ret = 0;
			goto done;
		}
		if (pos >= ret) {
			ret = 0; /* final read after getting everything */
			goto done;
		}
		*cntrp = cntr;
		for (i = 0; i < dd->cspec->ncntrs; i++)
			*cntr++ = read_6120_creg32(dd, cntr6120indices[i]);
	}
done:
	return ret;
}