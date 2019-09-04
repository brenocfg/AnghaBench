#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vio_dring_state {int dummy; } ;
struct TYPE_4__ {struct vio_dring_state* drings; } ;
struct vdc_port {TYPE_2__ vio; } ;
struct request_queue {int dummy; } ;
struct request {TYPE_1__* rq_disk; } ;
struct TYPE_3__ {struct vdc_port* private_data; } ;

/* Variables and functions */
 size_t VIO_DRIVER_TX_RING ; 
 scalar_t__ __send_request (struct request*) ; 
 struct request* blk_peek_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_requeue_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  blk_start_request (struct request*) ; 
 int /*<<< orphan*/  blk_stop_queue (struct request_queue*) ; 
 scalar_t__ unlikely (int) ; 
 int vdc_tx_dring_avail (struct vio_dring_state*) ; 

__attribute__((used)) static void do_vdc_request(struct request_queue *rq)
{
	struct request *req;

	while ((req = blk_peek_request(rq)) != NULL) {
		struct vdc_port *port;
		struct vio_dring_state *dr;

		port = req->rq_disk->private_data;
		dr = &port->vio.drings[VIO_DRIVER_TX_RING];
		if (unlikely(vdc_tx_dring_avail(dr) < 1))
			goto wait;

		blk_start_request(req);

		if (__send_request(req) < 0) {
			blk_requeue_request(rq, req);
wait:
			/* Avoid pointless unplugs. */
			blk_stop_queue(rq);
			break;
		}
	}
}