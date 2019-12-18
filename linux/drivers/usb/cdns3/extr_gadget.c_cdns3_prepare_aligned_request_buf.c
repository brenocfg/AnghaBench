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
struct TYPE_2__ {scalar_t__ length; scalar_t__ buf; } ;
struct cdns3_request {int /*<<< orphan*/  flags; TYPE_1__ request; struct cdns3_aligned_buf* aligned_buf; struct cdns3_endpoint* priv_ep; } ;
struct cdns3_endpoint {scalar_t__ dir; struct cdns3_device* cdns3_dev; } ;
struct cdns3_device {int /*<<< orphan*/  aligned_buf_list; int /*<<< orphan*/  aligned_buf_wq; int /*<<< orphan*/  sysdev; } ;
struct cdns3_aligned_buf {scalar_t__ size; int in_use; int /*<<< orphan*/  buf; int /*<<< orphan*/  list; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  REQUEST_UNALIGNED ; 
 scalar_t__ USB_DIR_IN ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cdns3_aligned_buf*) ; 
 struct cdns3_aligned_buf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_freezable_wq ; 
 int /*<<< orphan*/  trace_cdns3_free_aligned_request (struct cdns3_request*) ; 
 int /*<<< orphan*/  trace_cdns3_prepare_aligned_request (struct cdns3_request*) ; 

__attribute__((used)) static int cdns3_prepare_aligned_request_buf(struct cdns3_request *priv_req)
{
	struct cdns3_endpoint *priv_ep = priv_req->priv_ep;
	struct cdns3_device *priv_dev = priv_ep->cdns3_dev;
	struct cdns3_aligned_buf *buf;

	/* check if buffer is aligned to 8. */
	if (!((uintptr_t)priv_req->request.buf & 0x7))
		return 0;

	buf = priv_req->aligned_buf;

	if (!buf || priv_req->request.length > buf->size) {
		buf = kzalloc(sizeof(*buf), GFP_ATOMIC);
		if (!buf)
			return -ENOMEM;

		buf->size = priv_req->request.length;

		buf->buf = dma_alloc_coherent(priv_dev->sysdev,
					      buf->size,
					      &buf->dma,
					      GFP_ATOMIC);
		if (!buf->buf) {
			kfree(buf);
			return -ENOMEM;
		}

		if (priv_req->aligned_buf) {
			trace_cdns3_free_aligned_request(priv_req);
			priv_req->aligned_buf->in_use = 0;
			queue_work(system_freezable_wq,
				   &priv_dev->aligned_buf_wq);
		}

		buf->in_use = 1;
		priv_req->aligned_buf = buf;

		list_add_tail(&buf->list,
			      &priv_dev->aligned_buf_list);
	}

	if (priv_ep->dir == USB_DIR_IN) {
		memcpy(buf->buf, priv_req->request.buf,
		       priv_req->request.length);
	}

	priv_req->flags |= REQUEST_UNALIGNED;
	trace_cdns3_prepare_aligned_request(priv_req);

	return 0;
}