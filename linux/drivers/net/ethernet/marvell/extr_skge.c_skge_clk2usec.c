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
typedef  int u32 ;
struct skge_hw {int dummy; } ;

/* Variables and functions */
 int hwkhz (struct skge_hw const*) ; 

__attribute__((used)) static inline u32 skge_clk2usec(const struct skge_hw *hw, u32 ticks)
{
	return (ticks * 1000) / hwkhz(hw);
}