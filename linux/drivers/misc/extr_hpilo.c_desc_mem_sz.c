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
 int L2_QENTRY_SZ ; 

__attribute__((used)) static inline int desc_mem_sz(int nr_entry)
{
	return nr_entry << L2_QENTRY_SZ;
}