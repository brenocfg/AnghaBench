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
struct vdc_port {TYPE_1__* disk; } ;
struct request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  __blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_fetch_request (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdc_queue_drain(struct vdc_port *port)
{
	struct request *req;

	while ((req = blk_fetch_request(port->disk->queue)) != NULL)
		__blk_end_request_all(req, BLK_STS_IOERR);
}