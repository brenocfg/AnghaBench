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
struct qib_filedata {int /*<<< orphan*/  pq; int /*<<< orphan*/  subctxt; struct qib_ctxtdata* rcd; } ;
struct qib_devdata {int flags; int /*<<< orphan*/  unit; TYPE_1__* pcidev; } ;
struct qib_ctxtdata {int /*<<< orphan*/  ctxt; struct qib_devdata* dd; } ;
struct file {struct qib_filedata* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int QIB_HAS_SEND_DMA ; 
 int /*<<< orphan*/  qib_user_sdma_queue_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_qib_user_sdma_queue_create(struct file *fp)
{
	struct qib_filedata *fd = fp->private_data;
	struct qib_ctxtdata *rcd = fd->rcd;
	struct qib_devdata *dd = rcd->dd;

	if (dd->flags & QIB_HAS_SEND_DMA) {

		fd->pq = qib_user_sdma_queue_create(&dd->pcidev->dev,
						    dd->unit,
						    rcd->ctxt,
						    fd->subctxt);
		if (!fd->pq)
			return -ENOMEM;
	}

	return 0;
}