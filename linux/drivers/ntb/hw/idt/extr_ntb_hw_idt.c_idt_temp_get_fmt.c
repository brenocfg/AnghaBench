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
 int idt_get_deg (long) ; 
 scalar_t__ idt_get_deg_frac (long) ; 

__attribute__((used)) static inline u8 idt_temp_get_fmt(long mdegC)
{
	return (idt_get_deg(mdegC) << 1) | (idt_get_deg_frac(mdegC) ? 1 : 0);
}