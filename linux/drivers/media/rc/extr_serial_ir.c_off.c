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
struct TYPE_2__ {int /*<<< orphan*/  off; int /*<<< orphan*/  on; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_MCR ; 
 TYPE_1__* hardware ; 
 int /*<<< orphan*/  soutp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ txsense ; 
 size_t type ; 

__attribute__((used)) static void off(void)
{
	if (txsense)
		soutp(UART_MCR, hardware[type].on);
	else
		soutp(UART_MCR, hardware[type].off);
}