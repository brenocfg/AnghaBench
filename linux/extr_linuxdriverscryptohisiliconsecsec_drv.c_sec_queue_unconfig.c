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
struct sec_queue {int dummy; } ;
struct sec_dev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sec_queue_free_ring_pages (struct sec_queue*) ; 
 int /*<<< orphan*/  sec_queue_unmap_io (struct sec_queue*) ; 

__attribute__((used)) static void sec_queue_unconfig(struct sec_dev_info *info,
			       struct sec_queue *queue)
{
	sec_queue_unmap_io(queue);
	sec_queue_free_ring_pages(queue);
}