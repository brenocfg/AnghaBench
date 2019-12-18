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
 int /*<<< orphan*/  CLAMPCFG ; 
 int /*<<< orphan*/  CSCCTL ; 
 int /*<<< orphan*/  DFCCTL ; 
 int /*<<< orphan*/  LINCFG0 ; 
 int /*<<< orphan*/  regw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isif_disable_all_modules(void)
{
	/* disable BC */
	regw(0, CLAMPCFG);
	/* disable vdfc */
	regw(0, DFCCTL);
	/* disable CSC */
	regw(0, CSCCTL);
	/* disable linearization */
	regw(0, LINCFG0);
	/* disable other modules here as they are supported */
}