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
 int /*<<< orphan*/  ep93xx_devcfg_set_clear (unsigned int,int) ; 

__attribute__((used)) static inline void ep93xx_devcfg_set_bits(unsigned int bits)
{
	ep93xx_devcfg_set_clear(bits, 0x00);
}