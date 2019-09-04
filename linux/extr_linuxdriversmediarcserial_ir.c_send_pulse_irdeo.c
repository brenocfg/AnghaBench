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
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int duty_cycle; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_LSR ; 
 int UART_LSR_TEMT ; 
 int UART_LSR_THRE ; 
 int /*<<< orphan*/  UART_TX ; 
 TYPE_1__ serial_ir ; 
 int sinp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soutp (int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void send_pulse_irdeo(unsigned int length, ktime_t target)
{
	long rawbits;
	int i;
	unsigned char output;
	unsigned char chunk, shifted;

	/* how many bits have to be sent ? */
	rawbits = length * 1152 / 10000;
	if (serial_ir.duty_cycle > 50)
		chunk = 3;
	else
		chunk = 1;
	for (i = 0, output = 0x7f; rawbits > 0; rawbits -= 3) {
		shifted = chunk << (i * 3);
		shifted >>= 1;
		output &= (~shifted);
		i++;
		if (i == 3) {
			soutp(UART_TX, output);
			while (!(sinp(UART_LSR) & UART_LSR_THRE))
				;
			output = 0x7f;
			i = 0;
		}
	}
	if (i != 0) {
		soutp(UART_TX, output);
		while (!(sinp(UART_LSR) & UART_LSR_TEMT))
			;
	}
}