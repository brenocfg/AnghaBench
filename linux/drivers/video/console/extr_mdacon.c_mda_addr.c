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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 unsigned int mda_num_columns ; 
 int /*<<< orphan*/ * mda_vram_base ; 

__attribute__((used)) static inline u16 *mda_addr(unsigned int x, unsigned int y)
{
	return mda_vram_base + y * mda_num_columns + x;
}