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
struct resource {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 unsigned long inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void supermicro_old_pre_start(struct resource *smires)
{
	unsigned long val32;

	/* Bit 13: TCO_EN -> 0 = Disables TCO logic generating an SMI# */
	val32 = inl(smires->start);
	val32 &= 0xffffdfff;	/* Turn off SMI clearing watchdog */
	outl(val32, smires->start);	/* Needed to activate watchdog */
}