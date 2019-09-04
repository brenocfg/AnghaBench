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
struct scif_endpt {size_t state; int /*<<< orphan*/  recvlock; } ;
typedef  scalar_t__ scif_epd_t ;
struct TYPE_3__ {int /*<<< orphan*/  this_device; } ;
struct TYPE_4__ {TYPE_1__ mdev; } ;

/* Variables and functions */
 int SCIF_RECV_BLOCK ; 
 int _scif_recv (scalar_t__,void*,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct scif_endpt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * scif_ep_states ; 
 TYPE_2__ scif_info ; 
 int scif_msg_param_check (scalar_t__,int,int) ; 

int scif_recv(scif_epd_t epd, void *msg, int len, int flags)
{
	struct scif_endpt *ep = (struct scif_endpt *)epd;
	int ret;

	dev_dbg(scif_info.mdev.this_device,
		"SCIFAPI recv (K): ep %p %s\n", ep, scif_ep_states[ep->state]);
	if (!len)
		return 0;

	ret = scif_msg_param_check(epd, len, flags);
	if (ret)
		return ret;
	/*
	 * Grab the mutex lock in the blocking case only
	 * to ensure messages do not get fragmented/reordered.
	 * The non blocking mode is protected using spin locks
	 * in _scif_send().
	 */
	if (flags & SCIF_RECV_BLOCK)
		mutex_lock(&ep->recvlock);

	ret = _scif_recv(epd, msg, len, flags);

	if (flags & SCIF_RECV_BLOCK)
		mutex_unlock(&ep->recvlock);

	return ret;
}