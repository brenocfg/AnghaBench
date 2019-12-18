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
struct ccw_request {int lpm; int singlepath; int /*<<< orphan*/  callback; int /*<<< orphan*/  maxretries; int /*<<< orphan*/  timeout; } ;
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_2__ {struct ccw_request req; } ;

/* Variables and functions */
 int /*<<< orphan*/  PGID_RETRIES ; 
 int /*<<< orphan*/  PGID_TIMEOUT ; 
 int /*<<< orphan*/  memset (struct ccw_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spid_callback ; 
 int /*<<< orphan*/  spid_do (struct ccw_device*) ; 

__attribute__((used)) static void spid_start(struct ccw_device *cdev)
{
	struct ccw_request *req = &cdev->private->req;

	/* Initialize request data. */
	memset(req, 0, sizeof(*req));
	req->timeout	= PGID_TIMEOUT;
	req->maxretries	= PGID_RETRIES;
	req->lpm	= 0x80;
	req->singlepath	= 1;
	req->callback	= spid_callback;
	spid_do(cdev);
}