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
 int LOAD_FRAC (unsigned long) ; 
 int LOAD_INT (unsigned long) ; 

__attribute__((used)) static inline int get_loadavg(unsigned long load)
{
	return LOAD_INT(load) * 10 + LOAD_FRAC(load) / 10;
}