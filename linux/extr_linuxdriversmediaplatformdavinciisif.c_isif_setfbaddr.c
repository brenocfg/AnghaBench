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
 int /*<<< orphan*/  CADL ; 
 int /*<<< orphan*/  CADU ; 
 int /*<<< orphan*/  regw (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isif_setfbaddr(unsigned long addr)
{
	regw((addr >> 21) & 0x07ff, CADU);
	regw((addr >> 5) & 0x0ffff, CADL);
}