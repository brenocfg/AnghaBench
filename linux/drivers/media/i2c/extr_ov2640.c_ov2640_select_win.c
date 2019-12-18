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
struct ov2640_win_size {scalar_t__ width; scalar_t__ height; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ov2640_win_size const*) ; 
 struct ov2640_win_size const* ov2640_supported_win_sizes ; 

__attribute__((used)) static const struct ov2640_win_size *ov2640_select_win(u32 width, u32 height)
{
	int i, default_size = ARRAY_SIZE(ov2640_supported_win_sizes) - 1;

	for (i = 0; i < ARRAY_SIZE(ov2640_supported_win_sizes); i++) {
		if (ov2640_supported_win_sizes[i].width  >= width &&
		    ov2640_supported_win_sizes[i].height >= height)
			return &ov2640_supported_win_sizes[i];
	}

	return &ov2640_supported_win_sizes[default_size];
}