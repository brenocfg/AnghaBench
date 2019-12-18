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
struct raw3270_request {TYPE_1__* view; } ;
struct raw3270 {int dummy; } ;
struct TYPE_2__ {struct raw3270* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw3270_size_device (struct raw3270*) ; 
 int /*<<< orphan*/  raw3270_size_device_done (struct raw3270*) ; 

__attribute__((used)) static void
raw3270_read_modified_cb(struct raw3270_request *rq, void *data)
{
	struct raw3270 *rp = rq->view->dev;

	raw3270_size_device(rp);
	raw3270_size_device_done(rp);
}