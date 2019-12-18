#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct soc_pcmcia_socket {int dummy; } ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ socket_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_NR_PALMTX_PCMCIA_POWER1 ; 
 int /*<<< orphan*/  GPIO_NR_PALMTX_PCMCIA_POWER2 ; 
 int /*<<< orphan*/  GPIO_NR_PALMTX_PCMCIA_RESET ; 
 int SS_RESET ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
palmtx_pcmcia_configure_socket(struct soc_pcmcia_socket *skt,
				const socket_state_t *state)
{
	gpio_set_value(GPIO_NR_PALMTX_PCMCIA_POWER1, 1);
	gpio_set_value(GPIO_NR_PALMTX_PCMCIA_POWER2, 1);
	gpio_set_value(GPIO_NR_PALMTX_PCMCIA_RESET,
			!!(state->flags & SS_RESET));

	return 0;
}