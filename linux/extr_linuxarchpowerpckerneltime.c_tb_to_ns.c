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
 unsigned long long mulhdu (unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_to_ns_scale ; 
 unsigned long long tb_to_ns_shift ; 

unsigned long long tb_to_ns(unsigned long long ticks)
{
	return mulhdu(ticks, tb_to_ns_scale) << tb_to_ns_shift;
}