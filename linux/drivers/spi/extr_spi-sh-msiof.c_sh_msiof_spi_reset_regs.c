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
typedef  int u32 ;
struct sh_msiof_spi_priv {scalar_t__ mapbase; } ;

/* Variables and functions */
 scalar_t__ CTR ; 
 int CTR_RXRST ; 
 int CTR_TXRST ; 
 int /*<<< orphan*/  readl_poll_timeout_atomic (scalar_t__,int,int,int,int) ; 
 int sh_msiof_read (struct sh_msiof_spi_priv*,scalar_t__) ; 
 int /*<<< orphan*/  sh_msiof_write (struct sh_msiof_spi_priv*,scalar_t__,int) ; 

__attribute__((used)) static void sh_msiof_spi_reset_regs(struct sh_msiof_spi_priv *p)
{
	u32 mask = CTR_TXRST | CTR_RXRST;
	u32 data;

	data = sh_msiof_read(p, CTR);
	data |= mask;
	sh_msiof_write(p, CTR, data);

	readl_poll_timeout_atomic(p->mapbase + CTR, data, !(data & mask), 1,
				  100);
}