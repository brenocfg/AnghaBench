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

__attribute__((used)) static void broken_bios_stop(struct resource *smires)
{
	unsigned long val32;

	val32 = inl(smires->start);
	/* Bit 13: TCO_EN     -> 1 = Enables TCO logic generating an SMI#
	   Bit  0: GBL_SMI_EN -> 1 = Turn global SMI on again. */
	val32 |= 0x00002001;
	outl(val32, smires->start);
}