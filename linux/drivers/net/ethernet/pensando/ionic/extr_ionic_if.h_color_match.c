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
typedef  int u8 ;

/* Variables and functions */
 int IONIC_COMP_COLOR_MASK ; 

__attribute__((used)) static inline u8 color_match(u8 color, u8 done_color)
{
	return (!!(color & IONIC_COMP_COLOR_MASK)) == done_color;
}