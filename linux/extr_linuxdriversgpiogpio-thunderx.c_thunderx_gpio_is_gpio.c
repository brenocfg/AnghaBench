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
struct thunderx_gpio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_RATELIMIT (int,char*,unsigned int) ; 
 int thunderx_gpio_is_gpio_nowarn (struct thunderx_gpio*,unsigned int) ; 

__attribute__((used)) static bool thunderx_gpio_is_gpio(struct thunderx_gpio *txgpio,
				  unsigned int line)
{
	bool rv = thunderx_gpio_is_gpio_nowarn(txgpio, line);

	WARN_RATELIMIT(!rv, "Pin %d not available for GPIO\n", line);

	return rv;
}