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
typedef  long u32 ;

/* Variables and functions */
 long intlog10 (long) ; 

__attribute__((used)) static inline u32 log10times100(u32 value)
{
	return (100L * intlog10(value)) >> 24;
}