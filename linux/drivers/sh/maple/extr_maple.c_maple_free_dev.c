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
struct maple_device {struct maple_device* mq; int /*<<< orphan*/  recvbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct maple_device*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maple_queue_cache ; 

__attribute__((used)) static void maple_free_dev(struct maple_device *mdev)
{
	kmem_cache_free(maple_queue_cache, mdev->mq->recvbuf);
	kfree(mdev->mq);
	kfree(mdev);
}