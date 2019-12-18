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
typedef  char u8 ;
typedef  char u32 ;
struct sifive_serial_port {int dummy; } ;

/* Variables and functions */
 char SIFIVE_SERIAL_RXDATA_DATA_MASK ; 
 char SIFIVE_SERIAL_RXDATA_DATA_SHIFT ; 
 char SIFIVE_SERIAL_RXDATA_EMPTY_MASK ; 
 char SIFIVE_SERIAL_RXDATA_EMPTY_SHIFT ; 
 int /*<<< orphan*/  SIFIVE_SERIAL_RXDATA_OFFS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 char __ssp_readl (struct sifive_serial_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char __ssp_receive_char(struct sifive_serial_port *ssp, char *is_empty)
{
	u32 v;
	u8 ch;

	v = __ssp_readl(ssp, SIFIVE_SERIAL_RXDATA_OFFS);

	if (!is_empty)
		WARN_ON(1);
	else
		*is_empty = (v & SIFIVE_SERIAL_RXDATA_EMPTY_MASK) >>
			SIFIVE_SERIAL_RXDATA_EMPTY_SHIFT;

	ch = (v & SIFIVE_SERIAL_RXDATA_DATA_MASK) >>
		SIFIVE_SERIAL_RXDATA_DATA_SHIFT;

	return ch;
}