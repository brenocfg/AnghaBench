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
struct device {int dummy; } ;
struct cc_req_mgr_handle {unsigned int req_queue_tail; unsigned int req_queue_head; unsigned int axi_completed; struct cc_crypto_req* req_queue; } ;
struct cc_drvdata {struct cc_req_mgr_handle* request_mgr_handle; } ;
struct cc_crypto_req {int /*<<< orphan*/  user_arg; int /*<<< orphan*/  (* user_cb ) (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int MAX_REQUEST_QUEUE_SIZE ; 
 int /*<<< orphan*/  cc_pm_put_suspend (struct device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 
 int /*<<< orphan*/  stub1 (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void proc_completions(struct cc_drvdata *drvdata)
{
	struct cc_crypto_req *cc_req;
	struct device *dev = drvdata_to_dev(drvdata);
	struct cc_req_mgr_handle *request_mgr_handle =
						drvdata->request_mgr_handle;
	unsigned int *tail = &request_mgr_handle->req_queue_tail;
	unsigned int *head = &request_mgr_handle->req_queue_head;

	while (request_mgr_handle->axi_completed) {
		request_mgr_handle->axi_completed--;

		/* Dequeue request */
		if (*head == *tail) {
			/* We are supposed to handle a completion but our
			 * queue is empty. This is not normal. Return and
			 * hope for the best.
			 */
			dev_err(dev, "Request queue is empty head == tail %u\n",
				*head);
			break;
		}

		cc_req = &request_mgr_handle->req_queue[*tail];

		if (cc_req->user_cb)
			cc_req->user_cb(dev, cc_req->user_arg, 0);
		*tail = (*tail + 1) & (MAX_REQUEST_QUEUE_SIZE - 1);
		dev_dbg(dev, "Dequeue request tail=%u\n", *tail);
		dev_dbg(dev, "Request completed. axi_completed=%d\n",
			request_mgr_handle->axi_completed);
		cc_pm_put_suspend(dev);
	}
}