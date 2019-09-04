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
struct stm32_cryp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYP_IMSCR ; 
 int IMSCR_IN ; 
 int IMSCR_OUT ; 
 int /*<<< orphan*/  stm32_cryp_write (struct stm32_cryp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stm32_cryp_cpu_start(struct stm32_cryp *cryp)
{
	/* Enable interrupt and let the IRQ handler do everything */
	stm32_cryp_write(cryp, CRYP_IMSCR, IMSCR_IN | IMSCR_OUT);

	return 0;
}