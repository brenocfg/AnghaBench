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
struct i40e_vsi {TYPE_1__* back; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int I40E_FLAG_LEGACY_RX ; 
 int I40E_RXBUFFER_2048 ; 
 int I40E_RXBUFFER_3072 ; 
 int PAGE_SIZE ; 

__attribute__((used)) static int i40e_max_xdp_frame_size(struct i40e_vsi *vsi)
{
	if (PAGE_SIZE >= 8192 || (vsi->back->flags & I40E_FLAG_LEGACY_RX))
		return I40E_RXBUFFER_2048;
	else
		return I40E_RXBUFFER_3072;
}