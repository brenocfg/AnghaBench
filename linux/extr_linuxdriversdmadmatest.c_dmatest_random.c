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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  prandom_bytes (unsigned long*,int) ; 

__attribute__((used)) static unsigned long dmatest_random(void)
{
	unsigned long buf;

	prandom_bytes(&buf, sizeof(buf));
	return buf;
}