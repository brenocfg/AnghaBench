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
 int /*<<< orphan*/  B1_RESET ; 
 int /*<<< orphan*/  b1outp (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static inline void b1_reset(unsigned int base)
{
	b1outp(base, B1_RESET, 0);
	mdelay(55 * 2);	/* 2 TIC's */

	b1outp(base, B1_RESET, 1);
	mdelay(55 * 2);	/* 2 TIC's */

	b1outp(base, B1_RESET, 0);
	mdelay(55 * 2);	/* 2 TIC's */
}