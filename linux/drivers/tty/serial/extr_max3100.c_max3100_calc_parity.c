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
typedef  int u16 ;
struct max3100_port {int parity; } ;

/* Variables and functions */
 int MAX3100_7BIT ; 
 int MAX3100_PARITY_ON ; 
 int max3100_do_parity (struct max3100_port*,int) ; 

__attribute__((used)) static void max3100_calc_parity(struct max3100_port *s, u16 *c)
{
	if (s->parity & MAX3100_7BIT)
		*c &= 0x7f;
	else
		*c &= 0xff;

	if (s->parity & MAX3100_PARITY_ON)
		*c |= max3100_do_parity(s, *c) << 8;
}