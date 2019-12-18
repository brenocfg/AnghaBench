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
typedef  int u64 ;
typedef  size_t u32 ;

/* Variables and functions */
 int OV8856_DATA_LANES ; 
 int /*<<< orphan*/  OV8856_RGB_DEPTH ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 int* link_freq_menu_items ; 

__attribute__((used)) static u64 to_pixel_rate(u32 f_index)
{
	u64 pixel_rate = link_freq_menu_items[f_index] * 2 * OV8856_DATA_LANES;

	do_div(pixel_rate, OV8856_RGB_DEPTH);

	return pixel_rate;
}