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
struct vhost_net_buf {scalar_t__ tail; scalar_t__ head; } ;

/* Variables and functions */

__attribute__((used)) static void vhost_net_buf_init(struct vhost_net_buf *rxq)
{
	rxq->head = rxq->tail = 0;
}