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
struct xdp_buff {int dummy; } ;
struct i40e_ring {int dummy; } ;

/* Variables and functions */
 int I40E_XDP_CONSUMED ; 
 struct xdp_frame* convert_to_xdp_frame (struct xdp_buff*) ; 
 int i40e_xmit_xdp_ring (struct xdp_frame*,struct i40e_ring*) ; 
 scalar_t__ unlikely (int) ; 

int i40e_xmit_xdp_tx_ring(struct xdp_buff *xdp, struct i40e_ring *xdp_ring)
{
	struct xdp_frame *xdpf = convert_to_xdp_frame(xdp);

	if (unlikely(!xdpf))
		return I40E_XDP_CONSUMED;

	return i40e_xmit_xdp_ring(xdpf, xdp_ring);
}