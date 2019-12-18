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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;

/* Variables and functions */
 int MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  miss_address_31_6 ; 
 int /*<<< orphan*/  miss_address_39_32 ; 
 int /*<<< orphan*/  ste_rx_steering_mult ; 

u64 mlx5dr_ste_get_miss_addr(u8 *hw_ste)
{
	u64 index =
		(MLX5_GET(ste_rx_steering_mult, hw_ste, miss_address_31_6) |
		 MLX5_GET(ste_rx_steering_mult, hw_ste, miss_address_39_32) << 26);

	return index << 6;
}