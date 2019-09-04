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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAFR ; 
 int /*<<< orphan*/  GPDR ; 
 int /*<<< orphan*/  GPIO_32_768kHz ; 
 scalar_t__ TUCR ; 

__attribute__((used)) static void clk_gpio27_disable(struct clk *clk)
{
	TUCR = 0;
	GPDR &= ~GPIO_32_768kHz;
	GAFR &= ~GPIO_32_768kHz;
}