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
typedef  int /*<<< orphan*/  u8 ;
struct jsm_channel {TYPE_1__* ch_cls_uart; } ;
struct TYPE_2__ {int /*<<< orphan*/  ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IER_RDI ; 
 int /*<<< orphan*/  readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cls_enable_receiver(struct jsm_channel *ch)
{
	u8 tmp = readb(&ch->ch_cls_uart->ier);

	tmp |= (UART_IER_RDI);
	writeb(tmp, &ch->ch_cls_uart->ier);
}