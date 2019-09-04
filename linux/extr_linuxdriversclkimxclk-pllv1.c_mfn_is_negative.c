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
struct clk_pllv1 {int dummy; } ;

/* Variables and functions */
 unsigned int MFN_SIGN ; 
 int /*<<< orphan*/  is_imx1_pllv1 (struct clk_pllv1*) ; 
 int /*<<< orphan*/  is_imx21_pllv1 (struct clk_pllv1*) ; 

__attribute__((used)) static inline bool mfn_is_negative(struct clk_pllv1 *pll, unsigned int mfn)
{
	return !is_imx1_pllv1(pll) && !is_imx21_pllv1(pll) && (mfn & MFN_SIGN);
}