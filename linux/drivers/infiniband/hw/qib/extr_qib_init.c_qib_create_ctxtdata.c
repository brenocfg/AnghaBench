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
typedef  size_t u32 ;
struct qib_pportdata {struct qib_devdata* dd; } ;
struct qib_devdata {size_t first_user_ctxt; int rcvegrbufsize; int /*<<< orphan*/  (* f_init_ctxt ) (struct qib_ctxtdata*) ;struct qib_ctxtdata** rcd; } ;
struct qib_ctxtdata {int node_id; int cnt; size_t ctxt; int rcvegrbuf_size; int rcvegrbufs_perchunk; int rcvegrbuf_chunks; int rcvegrcnt; int /*<<< orphan*/  rcvegrbufs_perchunk_shift; void* opstats; struct qib_devdata* dd; struct qib_pportdata* ppd; int /*<<< orphan*/  qp_wait_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  kfree (struct qib_ctxtdata*) ; 
 void* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*) ; 
 int /*<<< orphan*/  stub1 (struct qib_ctxtdata*) ; 

struct qib_ctxtdata *qib_create_ctxtdata(struct qib_pportdata *ppd, u32 ctxt,
	int node_id)
{
	struct qib_devdata *dd = ppd->dd;
	struct qib_ctxtdata *rcd;

	rcd = kzalloc_node(sizeof(*rcd), GFP_KERNEL, node_id);
	if (rcd) {
		INIT_LIST_HEAD(&rcd->qp_wait_list);
		rcd->node_id = node_id;
		rcd->ppd = ppd;
		rcd->dd = dd;
		rcd->cnt = 1;
		rcd->ctxt = ctxt;
		dd->rcd[ctxt] = rcd;
#ifdef CONFIG_DEBUG_FS
		if (ctxt < dd->first_user_ctxt) { /* N/A for PSM contexts */
			rcd->opstats = kzalloc_node(sizeof(*rcd->opstats),
				GFP_KERNEL, node_id);
			if (!rcd->opstats) {
				kfree(rcd);
				qib_dev_err(dd,
					"Unable to allocate per ctxt stats buffer\n");
				return NULL;
			}
		}
#endif
		dd->f_init_ctxt(rcd);

		/*
		 * To avoid wasting a lot of memory, we allocate 32KB chunks
		 * of physically contiguous memory, advance through it until
		 * used up and then allocate more.  Of course, we need
		 * memory to store those extra pointers, now.  32KB seems to
		 * be the most that is "safe" under memory pressure
		 * (creating large files and then copying them over
		 * NFS while doing lots of MPI jobs).  The OOM killer can
		 * get invoked, even though we say we can sleep and this can
		 * cause significant system problems....
		 */
		rcd->rcvegrbuf_size = 0x8000;
		rcd->rcvegrbufs_perchunk =
			rcd->rcvegrbuf_size / dd->rcvegrbufsize;
		rcd->rcvegrbuf_chunks = (rcd->rcvegrcnt +
			rcd->rcvegrbufs_perchunk - 1) /
			rcd->rcvegrbufs_perchunk;
		rcd->rcvegrbufs_perchunk_shift =
			ilog2(rcd->rcvegrbufs_perchunk);
	}
	return rcd;
}