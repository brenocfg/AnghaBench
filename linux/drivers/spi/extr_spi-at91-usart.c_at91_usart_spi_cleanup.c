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
struct spi_device {struct at91_usart_spi_device* controller_state; } ;
struct at91_usart_spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct at91_usart_spi_device*) ; 

__attribute__((used)) static void at91_usart_spi_cleanup(struct spi_device *spi)
{
	struct at91_usart_spi_device *ausd = spi->controller_state;

	spi->controller_state = NULL;
	kfree(ausd);
}