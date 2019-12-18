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
struct pcmcia_socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_BATTDEAD ; 
 int /*<<< orphan*/  GPIO_BATTWARN ; 
 int /*<<< orphan*/  GPIO_CDA ; 
 int /*<<< orphan*/  GPIO_CDB ; 
 int /*<<< orphan*/  GPIO_OUTEN ; 
 int /*<<< orphan*/  GPIO_POWER ; 
 int /*<<< orphan*/  GPIO_RESET ; 
 int /*<<< orphan*/  GPIO_VSH ; 
 int /*<<< orphan*/  GPIO_VSL ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xxs1500_pcmcia_sock_init(struct pcmcia_socket *skt)
{
	gpio_direction_input(GPIO_CDA);
	gpio_direction_input(GPIO_CDB);
	gpio_direction_input(GPIO_VSL);
	gpio_direction_input(GPIO_VSH);
	gpio_direction_input(GPIO_BATTDEAD);
	gpio_direction_input(GPIO_BATTWARN);
	gpio_direction_output(GPIO_RESET, 1);	/* assert reset */
	gpio_direction_output(GPIO_OUTEN, 1);	/* disable buffers */
	gpio_direction_output(GPIO_POWER, 1);	/* power off */

	return 0;
}