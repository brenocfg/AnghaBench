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
typedef  int /*<<< orphan*/  u32 ;
struct spi_message {struct spi_device* spi; } ;
struct spi_device {int /*<<< orphan*/ * controller_state; } ;
struct spi_controller {int dummy; } ;
struct at91_usart_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  MR ; 
 int /*<<< orphan*/  US_ENABLE ; 
 int /*<<< orphan*/  US_OVRE_RXRDY_IRQS ; 
 int /*<<< orphan*/  at91_usart_spi_writel (struct at91_usart_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct at91_usart_spi* spi_master_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static int at91_usart_spi_prepare_message(struct spi_controller *ctlr,
					  struct spi_message *message)
{
	struct at91_usart_spi *aus = spi_master_get_devdata(ctlr);
	struct spi_device *spi = message->spi;
	u32 *ausd = spi->controller_state;

	at91_usart_spi_writel(aus, CR, US_ENABLE);
	at91_usart_spi_writel(aus, IER, US_OVRE_RXRDY_IRQS);
	at91_usart_spi_writel(aus, MR, *ausd);

	return 0;
}