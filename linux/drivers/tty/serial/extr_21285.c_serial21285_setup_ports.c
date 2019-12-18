#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int uartclk; } ;

/* Variables and functions */
 int mem_fclk_21285 ; 
 TYPE_1__ serial21285_port ; 

__attribute__((used)) static void serial21285_setup_ports(void)
{
	serial21285_port.uartclk = mem_fclk_21285 / 4;
}