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

/* Variables and functions */
 int /*<<< orphan*/  SPRN_TCR ; 
 int TCR_WIE ; 
 int WDTP_MASK ; 
 int /*<<< orphan*/  __booke_wdt_ping (int /*<<< orphan*/ *) ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __booke_wdt_disable(void *data)
{
	u32 val;

	val = mfspr(SPRN_TCR);
	val &= ~(TCR_WIE | WDTP_MASK);
	mtspr(SPRN_TCR, val);

	/* clear status to make sure nothing is pending */
	__booke_wdt_ping(NULL);

}