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

__attribute__((used)) static inline void indy_sc_wipe(unsigned long first, unsigned long last)
{
	unsigned long tmp;

	__asm__ __volatile__(
	"	.set	push			# indy_sc_wipe		\n"
	"	.set	noreorder					\n"
	"	.set	mips3						\n"
	"	.set	noat						\n"
	"	mfc0	%2, $12						\n"
	"	li	$1, 0x80		# Go 64 bit		\n"
	"	mtc0	$1, $12						\n"
	"								\n"
	"	#							\n"
	"	# Open code a dli $1, 0x9000000080000000		\n"
	"	#							\n"
	"	# Required because binutils 2.25 will happily accept	\n"
	"	# 64 bit instructions in .set mips3 mode but puke on	\n"
	"	# 64 bit constants when generating 32 bit ELF		\n"
	"	#							\n"
	"	lui	$1,0x9000					\n"
	"	dsll	$1,$1,0x10					\n"
	"	ori	$1,$1,0x8000					\n"
	"	dsll	$1,$1,0x10					\n"
	"								\n"
	"	or	%0, $1			# first line to flush	\n"
	"	or	%1, $1			# last line to flush	\n"
	"	.set	at						\n"
	"								\n"
	"1:	sw	$0, 0(%0)					\n"
	"	bne	%0, %1, 1b					\n"
	"	 daddu	%0, 32						\n"
	"								\n"
	"	mtc0	%2, $12			# Back to 32 bit	\n"
	"	nop				# pipeline hazard	\n"
	"	nop							\n"
	"	nop							\n"
	"	nop							\n"
	"	.set	pop						\n"
	: "=r" (first), "=r" (last), "=&r" (tmp)
	: "0" (first), "1" (last));
}