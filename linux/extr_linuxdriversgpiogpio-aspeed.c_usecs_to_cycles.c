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
typedef  unsigned long u64 ;
typedef  unsigned long u32 ;
struct aspeed_gpio {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int ERANGE ; 
 unsigned long U32_MAX ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 unsigned long do_div (unsigned long,int) ; 

__attribute__((used)) static int usecs_to_cycles(struct aspeed_gpio *gpio, unsigned long usecs,
		u32 *cycles)
{
	u64 rate;
	u64 n;
	u32 r;

	rate = clk_get_rate(gpio->clk);
	if (!rate)
		return -ENOTSUPP;

	n = rate * usecs;
	r = do_div(n, 1000000);

	if (n >= U32_MAX)
		return -ERANGE;

	/* At least as long as the requested time */
	*cycles = n + (!!r);

	return 0;
}