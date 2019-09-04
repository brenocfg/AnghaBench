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
typedef  int u32 ;
struct qib_user_info {int dummy; } ;
struct qib_pportdata {int dummy; } ;
struct qib_devdata {int first_user_ctxt; int cfgctxts; int num_pports; struct qib_pportdata* pport; scalar_t__* rcd; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENETDOWN ; 
 int setup_ctxt (struct qib_pportdata*,int,struct file*,struct qib_user_info const*) ; 
 scalar_t__ usable (struct qib_pportdata*) ; 

__attribute__((used)) static int choose_port_ctxt(struct file *fp, struct qib_devdata *dd, u32 port,
			    const struct qib_user_info *uinfo)
{
	struct qib_pportdata *ppd = NULL;
	int ret, ctxt;

	if (port) {
		if (!usable(dd->pport + port - 1)) {
			ret = -ENETDOWN;
			goto done;
		} else
			ppd = dd->pport + port - 1;
	}
	for (ctxt = dd->first_user_ctxt; ctxt < dd->cfgctxts && dd->rcd[ctxt];
	     ctxt++)
		;
	if (ctxt == dd->cfgctxts) {
		ret = -EBUSY;
		goto done;
	}
	if (!ppd) {
		u32 pidx = ctxt % dd->num_pports;

		if (usable(dd->pport + pidx))
			ppd = dd->pport + pidx;
		else {
			for (pidx = 0; pidx < dd->num_pports && !ppd;
			     pidx++)
				if (usable(dd->pport + pidx))
					ppd = dd->pport + pidx;
		}
	}
	ret = ppd ? setup_ctxt(ppd, ctxt, fp, uinfo) : -ENETDOWN;
done:
	return ret;
}