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
typedef  int /*<<< orphan*/  u16 ;
struct virtnet_info {int dummy; } ;

/* Variables and functions */
 int _virtnet_set_queues (struct virtnet_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int virtnet_set_queues(struct virtnet_info *vi, u16 queue_pairs)
{
	int err;

	rtnl_lock();
	err = _virtnet_set_queues(vi, queue_pairs);
	rtnl_unlock();
	return err;
}