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
struct clocksource {int dummy; } ;

/* Variables and functions */
 scalar_t__* CSR_TIMER2_CNTL ; 

__attribute__((used)) static void cksrc_dc21285_disable(struct clocksource *cs)
{
	*CSR_TIMER2_CNTL = 0;
}