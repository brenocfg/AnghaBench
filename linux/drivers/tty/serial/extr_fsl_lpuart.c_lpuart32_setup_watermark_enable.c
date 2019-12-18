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
struct lpuart_port {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  UARTCTRL ; 
 int UARTCTRL_ILIE ; 
 int UARTCTRL_RE ; 
 int UARTCTRL_TE ; 
 int lpuart32_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpuart32_setup_watermark (struct lpuart_port*) ; 
 int /*<<< orphan*/  lpuart32_write (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpuart32_setup_watermark_enable(struct lpuart_port *sport)
{
	u32 temp;

	lpuart32_setup_watermark(sport);

	temp = lpuart32_read(&sport->port, UARTCTRL);
	temp |= UARTCTRL_RE | UARTCTRL_TE | UARTCTRL_ILIE;
	lpuart32_write(&sport->port, temp, UARTCTRL);
}