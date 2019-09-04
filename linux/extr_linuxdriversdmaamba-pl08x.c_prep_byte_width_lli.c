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
typedef  scalar_t__ u32 ;
struct pl08x_lli_build_data {int dummy; } ;
struct pl08x_driver_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pl08x_fill_lli_for_desc (struct pl08x_driver_data*,struct pl08x_lli_build_data*,int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ pl08x_lli_control_bits (struct pl08x_driver_data*,scalar_t__,int,int,scalar_t__) ; 

__attribute__((used)) static inline void prep_byte_width_lli(struct pl08x_driver_data *pl08x,
			struct pl08x_lli_build_data *bd, u32 *cctl, u32 len,
			int num_llis, size_t *total_bytes)
{
	*cctl = pl08x_lli_control_bits(pl08x, *cctl, 1, 1, len);
	pl08x_fill_lli_for_desc(pl08x, bd, num_llis, len, *cctl, len);
	(*total_bytes) += len;
}