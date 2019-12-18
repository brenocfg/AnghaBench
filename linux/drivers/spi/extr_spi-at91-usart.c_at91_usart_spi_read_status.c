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
struct at91_usart_spi {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR ; 
 int /*<<< orphan*/  at91_usart_spi_readl (struct at91_usart_spi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 at91_usart_spi_read_status(struct at91_usart_spi *aus)
{
	aus->status = at91_usart_spi_readl(aus, CSR);
	return aus->status;
}