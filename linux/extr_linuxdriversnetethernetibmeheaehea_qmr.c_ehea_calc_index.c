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
 unsigned long EHEA_INDEX_MASK ; 

__attribute__((used)) static inline int ehea_calc_index(unsigned long i, unsigned long s)
{
	return (i >> s) & EHEA_INDEX_MASK;
}