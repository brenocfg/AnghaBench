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

/* Variables and functions */
 unsigned int CCDC_SYNCEN_VDHDEN_MASK ; 
 int /*<<< orphan*/  SYNCEN ; 
 unsigned int regr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regw (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccdc_enable(int en)
{
	unsigned int temp;
	temp = regr(SYNCEN);
	temp &= (~CCDC_SYNCEN_VDHDEN_MASK);
	temp |= (en & CCDC_SYNCEN_VDHDEN_MASK);
	regw(temp, SYNCEN);
}