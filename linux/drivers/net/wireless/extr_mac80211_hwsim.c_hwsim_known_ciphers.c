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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__ const*) ; 
 scalar_t__ const* hwsim_ciphers ; 

__attribute__((used)) static bool hwsim_known_ciphers(const u32 *ciphers, int n_ciphers)
{
	int i;

	for (i = 0; i < n_ciphers; i++) {
		int j;
		int found = 0;

		for (j = 0; j < ARRAY_SIZE(hwsim_ciphers); j++) {
			if (ciphers[i] == hwsim_ciphers[j]) {
				found = 1;
				break;
			}
		}

		if (!found)
			return false;
	}

	return true;
}