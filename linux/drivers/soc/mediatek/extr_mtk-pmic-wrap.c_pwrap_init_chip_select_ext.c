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
struct pmic_wrapper {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWRAP_CSHEXT_READ ; 
 int /*<<< orphan*/  PWRAP_CSHEXT_WRITE ; 
 int /*<<< orphan*/  PWRAP_CSLEXT_END ; 
 int /*<<< orphan*/  PWRAP_CSLEXT_START ; 
 int /*<<< orphan*/  pwrap_writel (struct pmic_wrapper*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pwrap_init_chip_select_ext(struct pmic_wrapper *wrp, u8 hext_write,
				       u8 hext_read, u8 lext_start,
				       u8 lext_end)
{
	/*
	 * After finishing a write and read transaction, extends CS high time
	 * to be at least xT of BUS CLK as hext_write and hext_read specifies
	 * respectively.
	 */
	pwrap_writel(wrp, hext_write, PWRAP_CSHEXT_WRITE);
	pwrap_writel(wrp, hext_read, PWRAP_CSHEXT_READ);

	/*
	 * Extends CS low time after CSL and before CSH command to be at
	 * least xT of BUS CLK as lext_start and lext_end specifies
	 * respectively.
	 */
	pwrap_writel(wrp, lext_start, PWRAP_CSLEXT_START);
	pwrap_writel(wrp, lext_end, PWRAP_CSLEXT_END);
}