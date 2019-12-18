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
struct atyfb_par {scalar_t__ ati_regbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  in_8 (scalar_t__) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 

__attribute__((used)) static inline u8 aty_ld_8(int regindex, const struct atyfb_par *par)
{
	/* Hack for bloc 1, should be cleanly optimized by compiler */
	if (regindex >= 0x400)
		regindex -= 0x800;
#ifdef CONFIG_ATARI
	return in_8(par->ati_regbase + regindex);
#else
	return readb(par->ati_regbase + regindex);
#endif
}