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
 int /*<<< orphan*/  H_RANDOM ; 
 scalar_t__ H_SUCCESS ; 
 int PLPAR_HCALL_BUFSIZE ; 
 scalar_t__ plpar_hcall (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int pseries_get_random_long(unsigned long *v)
{
	unsigned long retbuf[PLPAR_HCALL_BUFSIZE];

	if (plpar_hcall(H_RANDOM, retbuf) == H_SUCCESS) {
		*v = retbuf[0];
		return 1;
	}

	return 0;
}