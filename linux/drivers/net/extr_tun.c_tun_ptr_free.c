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
struct xdp_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_array_destroy_skb (void*) ; 
 scalar_t__ tun_is_xdp_frame (void*) ; 
 struct xdp_frame* tun_ptr_to_xdp (void*) ; 
 int /*<<< orphan*/  xdp_return_frame (struct xdp_frame*) ; 

void tun_ptr_free(void *ptr)
{
	if (!ptr)
		return;
	if (tun_is_xdp_frame(ptr)) {
		struct xdp_frame *xdpf = tun_ptr_to_xdp(ptr);

		xdp_return_frame(xdpf);
	} else {
		__skb_array_destroy_skb(ptr);
	}
}