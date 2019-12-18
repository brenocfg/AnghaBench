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
 int /*<<< orphan*/  b1_tx_empty (unsigned int) ; 
 int /*<<< orphan*/  b1outp (unsigned int,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static inline void b1_put_byte(unsigned int base, unsigned char val)
{
	while (!b1_tx_empty(base));
	b1outp(base, B1_WRITE, val);
}