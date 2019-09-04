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
 int /*<<< orphan*/  iob () ; 
 scalar_t__* kn0x_erraddr ; 

__attribute__((used)) static inline void dec_ecc_be_ack(void)
{
	*kn0x_erraddr = 0;			/* any write clears the IRQ */
	iob();
}