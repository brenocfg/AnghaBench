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
struct rwdt_priv {int /*<<< orphan*/  clk_rate; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (unsigned int,int) ; 

__attribute__((used)) static void rwdt_wait_cycles(struct rwdt_priv *priv, unsigned int cycles)
{
	unsigned int delay;

	delay = DIV_ROUND_UP(cycles * 1000000, priv->clk_rate);

	usleep_range(delay, 2 * delay);
}