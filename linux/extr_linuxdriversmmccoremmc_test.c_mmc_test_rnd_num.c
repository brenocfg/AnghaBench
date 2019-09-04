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
typedef  unsigned int uint64_t ;

/* Variables and functions */
 int rnd_next ; 

__attribute__((used)) static unsigned int mmc_test_rnd_num(unsigned int rnd_cnt)
{
	uint64_t r;

	rnd_next = rnd_next * 1103515245 + 12345;
	r = (rnd_next >> 16) & 0x7fff;
	return (r * rnd_cnt) >> 15;
}