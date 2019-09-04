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
typedef  unsigned long u32 ;
struct clk_si514_muldiv {int m_frac; unsigned long hs_div; int /*<<< orphan*/  ls_div_bits; scalar_t__ m_int; } ;

/* Variables and functions */
 unsigned long BIT (int /*<<< orphan*/ ) ; 
 int FXO ; 

__attribute__((used)) static unsigned long si514_calc_rate(struct clk_si514_muldiv *settings)
{
	u64 m = settings->m_frac | ((u64)settings->m_int << 29);
	u32 d = settings->hs_div * BIT(settings->ls_div_bits);

	return ((u32)(((m * FXO) + (FXO / 2)) >> 29)) / d;
}