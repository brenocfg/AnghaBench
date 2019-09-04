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
struct hci_uart_proto {int dummy; } ;

/* Variables and functions */
 unsigned int HCI_UART_MAX_PROTO ; 
 struct hci_uart_proto const** hup ; 

__attribute__((used)) static const struct hci_uart_proto *hci_uart_get_proto(unsigned int id)
{
	if (id >= HCI_UART_MAX_PROTO)
		return NULL;

	return hup[id];
}