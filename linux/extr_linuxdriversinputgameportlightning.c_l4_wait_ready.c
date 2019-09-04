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
 int L4_BUSY ; 
 int /*<<< orphan*/  L4_PORT ; 
 unsigned int L4_TIMEOUT ; 
 int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l4_wait_ready(void)
{
	unsigned int t = L4_TIMEOUT;

	while ((inb(L4_PORT) & L4_BUSY) && t > 0) t--;
	return -(t <= 0);
}