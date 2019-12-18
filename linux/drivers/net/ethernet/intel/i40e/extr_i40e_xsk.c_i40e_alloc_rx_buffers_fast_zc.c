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
struct i40e_ring {int dummy; } ;

/* Variables and functions */
 int __i40e_alloc_rx_buffers_zc (struct i40e_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_alloc_buffer_zc ; 

__attribute__((used)) static bool i40e_alloc_rx_buffers_fast_zc(struct i40e_ring *rx_ring, u16 count)
{
	return __i40e_alloc_rx_buffers_zc(rx_ring, count,
					  i40e_alloc_buffer_zc);
}