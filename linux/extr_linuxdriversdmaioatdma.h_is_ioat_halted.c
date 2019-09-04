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
 unsigned long IOAT_CHANSTS_HALTED ; 
 unsigned long IOAT_CHANSTS_STATUS ; 

__attribute__((used)) static inline bool is_ioat_halted(unsigned long status)
{
	return ((status & IOAT_CHANSTS_STATUS) == IOAT_CHANSTS_HALTED);
}