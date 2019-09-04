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
typedef  int u32 ;
struct ace_device {int dummy; } ;

/* Variables and functions */
 int ace_in (struct ace_device*,int) ; 

__attribute__((used)) static inline u32 ace_in32(struct ace_device *ace, int reg)
{
	return ace_in(ace, reg) | (ace_in(ace, reg + 2) << 16);
}