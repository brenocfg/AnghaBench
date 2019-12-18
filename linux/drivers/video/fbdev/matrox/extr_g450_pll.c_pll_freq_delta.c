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

__attribute__((used)) static inline unsigned int pll_freq_delta(unsigned int f1, unsigned int f2) {
	if (f2 < f1) {
    		f2 = f1 - f2;
	} else {
		f2 = f2 - f1;
	}
	return f2;
}