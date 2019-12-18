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

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (void*) ; 
 scalar_t__ veth_is_xdp_frame (void*) ; 
 int /*<<< orphan*/  veth_ptr_to_xdp (void*) ; 
 int /*<<< orphan*/  xdp_return_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void veth_ptr_free(void *ptr)
{
	if (veth_is_xdp_frame(ptr))
		xdp_return_frame(veth_ptr_to_xdp(ptr));
	else
		kfree_skb(ptr);
}