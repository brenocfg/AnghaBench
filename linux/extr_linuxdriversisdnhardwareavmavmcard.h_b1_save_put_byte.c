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
 int /*<<< orphan*/  B1_WRITE ; 
 int HZ ; 
 int /*<<< orphan*/  b1_tx_empty (unsigned int) ; 
 int /*<<< orphan*/  b1outp (unsigned int,int /*<<< orphan*/ ,unsigned char) ; 
 int jiffies ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static inline int b1_save_put_byte(unsigned int base, unsigned char val)
{
	unsigned long stop = jiffies + 2 * HZ;
	while (!b1_tx_empty(base) && time_before(jiffies, stop));
	if (!b1_tx_empty(base)) return -1;
	b1outp(base, B1_WRITE, val);
	return 0;
}