#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ membase; } ;
struct lpuart_port {TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ UARTCR2 ; 
 unsigned char UARTCR2_RE ; 
 unsigned char UARTCR2_RIE ; 
 unsigned char UARTCR2_TE ; 
 int /*<<< orphan*/  lpuart_setup_watermark (struct lpuart_port*) ; 
 unsigned char readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (unsigned char,scalar_t__) ; 

__attribute__((used)) static void lpuart_setup_watermark_enable(struct lpuart_port *sport)
{
	unsigned char cr2;

	lpuart_setup_watermark(sport);

	cr2 = readb(sport->port.membase + UARTCR2);
	cr2 |= UARTCR2_RIE | UARTCR2_RE | UARTCR2_TE;
	writeb(cr2, sport->port.membase + UARTCR2);
}