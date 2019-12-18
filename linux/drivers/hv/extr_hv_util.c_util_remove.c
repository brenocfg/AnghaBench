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
struct hv_util_service {int /*<<< orphan*/  recv_buffer; int /*<<< orphan*/  (* util_deinit ) () ;} ;
struct hv_device {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 struct hv_util_service* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  vmbus_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int util_remove(struct hv_device *dev)
{
	struct hv_util_service *srv = hv_get_drvdata(dev);

	if (srv->util_deinit)
		srv->util_deinit();
	vmbus_close(dev->channel);
	kfree(srv->recv_buffer);

	return 0;
}