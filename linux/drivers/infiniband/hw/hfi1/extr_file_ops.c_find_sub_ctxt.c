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
typedef  scalar_t__ u16 ;
struct hfi1_user_info {int /*<<< orphan*/  subctxt_cnt; } ;
struct hfi1_filedata {struct hfi1_devdata* dd; } ;
struct hfi1_devdata {scalar_t__ first_dyn_alloc_ctxt; scalar_t__ num_rcv_contexts; } ;
struct hfi1_ctxtdata {int dummy; } ;

/* Variables and functions */
 struct hfi1_ctxtdata* hfi1_rcd_get_by_index (struct hfi1_devdata*,scalar_t__) ; 
 int /*<<< orphan*/  hfi1_rcd_put (struct hfi1_ctxtdata*) ; 
 int match_ctxt (struct hfi1_filedata*,struct hfi1_user_info const*,struct hfi1_ctxtdata*) ; 

__attribute__((used)) static int find_sub_ctxt(struct hfi1_filedata *fd,
			 const struct hfi1_user_info *uinfo)
{
	struct hfi1_ctxtdata *uctxt;
	struct hfi1_devdata *dd = fd->dd;
	u16 i;
	int ret;

	if (!uinfo->subctxt_cnt)
		return 0;

	for (i = dd->first_dyn_alloc_ctxt; i < dd->num_rcv_contexts; i++) {
		uctxt = hfi1_rcd_get_by_index(dd, i);
		if (uctxt) {
			ret = match_ctxt(fd, uinfo, uctxt);
			hfi1_rcd_put(uctxt);
			/* value of != 0 will return */
			if (ret)
				return ret;
		}
	}

	return 0;
}