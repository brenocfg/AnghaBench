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
struct uart_port {int dummy; } ;
struct s3c24xx_uart_info {unsigned int clksel_mask; scalar_t__ type; } ;
struct s3c2410_uartcfg {unsigned long ucon; unsigned long ufcon; } ;

/* Variables and functions */
 scalar_t__ PORT_S3C2440 ; 
 int /*<<< orphan*/  S3C2410_UCON ; 
 int /*<<< orphan*/  S3C2410_UFCON ; 
 unsigned long S3C2410_UFCON_RESETBOTH ; 
 unsigned int S3C2440_UCON0_DIVMASK ; 
 unsigned long rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 
 struct s3c24xx_uart_info* s3c24xx_port_to_info (struct uart_port*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wr_regl (struct uart_port*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void s3c24xx_serial_resetport(struct uart_port *port,
				   struct s3c2410_uartcfg *cfg)
{
	struct s3c24xx_uart_info *info = s3c24xx_port_to_info(port);
	unsigned long ucon = rd_regl(port, S3C2410_UCON);
	unsigned int ucon_mask;

	ucon_mask = info->clksel_mask;
	if (info->type == PORT_S3C2440)
		ucon_mask |= S3C2440_UCON0_DIVMASK;

	ucon &= ucon_mask;
	wr_regl(port, S3C2410_UCON,  ucon | cfg->ucon);

	/* reset both fifos */
	wr_regl(port, S3C2410_UFCON, cfg->ufcon | S3C2410_UFCON_RESETBOTH);
	wr_regl(port, S3C2410_UFCON, cfg->ufcon);

	/* some delay is required after fifo reset */
	udelay(1);
}