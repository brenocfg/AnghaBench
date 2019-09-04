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
struct ubd {size_t start_sg; size_t end_sg; struct request* request; scalar_t__ rq_pos; int /*<<< orphan*/  restart; struct scatterlist* sg; } ;
struct scatterlist {int length; int /*<<< orphan*/  offset; } ;
struct request_queue {struct ubd* queuedata; } ;
struct request {int dummy; } ;
struct io_thread_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ REQ_OP_FLUSH ; 
 struct request* blk_fetch_request (struct request_queue*) ; 
 size_t blk_rq_map_sg (struct request_queue*,struct request*,struct scatterlist*) ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 struct io_thread_req* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_flush_request (struct request*,struct io_thread_req*) ; 
 int /*<<< orphan*/  prepare_request (struct request*,struct io_thread_req*,unsigned long long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ req_op (struct request*) ; 
 int /*<<< orphan*/  restart ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int submit_request (struct io_thread_req*,struct ubd*) ; 

__attribute__((used)) static void do_ubd_request(struct request_queue *q)
{
	struct io_thread_req *io_req;
	struct request *req;

	while(1){
		struct ubd *dev = q->queuedata;
		if(dev->request == NULL){
			struct request *req = blk_fetch_request(q);
			if(req == NULL)
				return;

			dev->request = req;
			dev->rq_pos = blk_rq_pos(req);
			dev->start_sg = 0;
			dev->end_sg = blk_rq_map_sg(q, req, dev->sg);
		}

		req = dev->request;

		if (req_op(req) == REQ_OP_FLUSH) {
			io_req = kmalloc(sizeof(struct io_thread_req),
					 GFP_ATOMIC);
			if (io_req == NULL) {
				if (list_empty(&dev->restart))
					list_add(&dev->restart, &restart);
				return;
			}
			prepare_flush_request(req, io_req);
			if (submit_request(io_req, dev) == false)
				return;
		}

		while(dev->start_sg < dev->end_sg){
			struct scatterlist *sg = &dev->sg[dev->start_sg];

			io_req = kmalloc(sizeof(struct io_thread_req),
					 GFP_ATOMIC);
			if(io_req == NULL){
				if(list_empty(&dev->restart))
					list_add(&dev->restart, &restart);
				return;
			}
			prepare_request(req, io_req,
					(unsigned long long)dev->rq_pos << 9,
					sg->offset, sg->length, sg_page(sg));

			if (submit_request(io_req, dev) == false)
				return;

			dev->rq_pos += sg->length >> 9;
			dev->start_sg++;
		}
		dev->end_sg = 0;
		dev->request = NULL;
	}
}