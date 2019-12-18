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
struct vring {int dummy; } ;
struct virtqueue {int dummy; } ;
struct TYPE_3__ {struct vring const vring; } ;
struct TYPE_4__ {TYPE_1__ split; } ;

/* Variables and functions */
 TYPE_2__* to_vvq (struct virtqueue*) ; 

const struct vring *virtqueue_get_vring(struct virtqueue *vq)
{
	return &to_vvq(vq)->split.vring;
}