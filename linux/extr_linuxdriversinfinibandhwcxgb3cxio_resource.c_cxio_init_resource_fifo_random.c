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
typedef  int /*<<< orphan*/  u32 ;
struct kfifo {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int __cxio_init_resource_fifo (struct kfifo*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cxio_init_resource_fifo_random(struct kfifo *fifo,
				   spinlock_t * fifo_lock,
				   u32 nr, u32 skip_low, u32 skip_high)
{

	return (__cxio_init_resource_fifo(fifo, fifo_lock, nr, skip_low,
					  skip_high, 1));
}