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
struct xdp_frame {int len; } ;

/* Variables and functions */
 int __skb_array_len_with_tag (void*) ; 
 scalar_t__ likely (void*) ; 
 scalar_t__ tun_is_xdp_frame (void*) ; 
 struct xdp_frame* tun_ptr_to_xdp (void*) ; 

__attribute__((used)) static int tun_ptr_peek_len(void *ptr)
{
	if (likely(ptr)) {
		if (tun_is_xdp_frame(ptr)) {
			struct xdp_frame *xdpf = tun_ptr_to_xdp(ptr);

			return xdpf->len;
		}
		return __skb_array_len_with_tag(ptr);
	} else {
		return 0;
	}
}