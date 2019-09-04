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

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (scalar_t__,scalar_t__) ; 
 scalar_t__ roundup (scalar_t__,int) ; 

__attribute__((used)) static u32
dsi_hs_timing(u32 ui_ns, u32 ns, u32 ui)
{
	/* The HS timings have to be rounded up to a multiple of 8
	 * because we're using the byte clock.
	 */
	return roundup(ui + DIV_ROUND_UP(ns, ui_ns), 8);
}