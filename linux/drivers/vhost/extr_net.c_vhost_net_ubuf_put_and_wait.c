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
struct vhost_net_ubuf_ref {int /*<<< orphan*/  refcount; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_net_ubuf_put (struct vhost_net_ubuf_ref*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vhost_net_ubuf_put_and_wait(struct vhost_net_ubuf_ref *ubufs)
{
	vhost_net_ubuf_put(ubufs);
	wait_event(ubufs->wait, !atomic_read(&ubufs->refcount));
}