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
 int bch_strtoint_h (char const*,int*) ; 
 int bch_strtoll_h (char const*,long long*) ; 

__attribute__((used)) static inline int bch_strtol_h(const char *cp, long *res)
{
#if BITS_PER_LONG == 32
	return bch_strtoint_h(cp, (int *) res);
#else
	return bch_strtoll_h(cp, (long long *) res);
#endif
}