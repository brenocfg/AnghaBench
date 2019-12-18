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
typedef  int u16 ;
struct TYPE_2__ {int size; } ;
struct hfi1_ctxtdata {int subctxt_cnt; int /*<<< orphan*/ * subctxt_uregbase; int /*<<< orphan*/ * subctxt_rcvhdr_base; void* subctxt_rcvegrbuf; TYPE_1__ egrbufs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int rcvhdrq_size (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 void* vmalloc_user (int) ; 

__attribute__((used)) static int setup_subctxt(struct hfi1_ctxtdata *uctxt)
{
	int ret = 0;
	u16 num_subctxts = uctxt->subctxt_cnt;

	uctxt->subctxt_uregbase = vmalloc_user(PAGE_SIZE);
	if (!uctxt->subctxt_uregbase)
		return -ENOMEM;

	/* We can take the size of the RcvHdr Queue from the master */
	uctxt->subctxt_rcvhdr_base = vmalloc_user(rcvhdrq_size(uctxt) *
						  num_subctxts);
	if (!uctxt->subctxt_rcvhdr_base) {
		ret = -ENOMEM;
		goto bail_ureg;
	}

	uctxt->subctxt_rcvegrbuf = vmalloc_user(uctxt->egrbufs.size *
						num_subctxts);
	if (!uctxt->subctxt_rcvegrbuf) {
		ret = -ENOMEM;
		goto bail_rhdr;
	}

	return 0;

bail_rhdr:
	vfree(uctxt->subctxt_rcvhdr_base);
	uctxt->subctxt_rcvhdr_base = NULL;
bail_ureg:
	vfree(uctxt->subctxt_uregbase);
	uctxt->subctxt_uregbase = NULL;

	return ret;
}