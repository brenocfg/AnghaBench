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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ioread32 (unsigned int) ; 
 unsigned int rt288x_wdt_base ; 

__attribute__((used)) static inline u32 rt_wdt_r32(unsigned reg)
{
	return ioread32(rt288x_wdt_base + reg);
}