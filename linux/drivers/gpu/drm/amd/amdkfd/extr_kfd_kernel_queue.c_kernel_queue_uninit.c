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
struct TYPE_2__ {int /*<<< orphan*/  (* uninitialize ) (struct kernel_queue*) ;} ;
struct kernel_queue {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct kernel_queue*) ; 
 int /*<<< orphan*/  stub1 (struct kernel_queue*) ; 

void kernel_queue_uninit(struct kernel_queue *kq)
{
	kq->ops.uninitialize(kq);
	kfree(kq);
}