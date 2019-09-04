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

/* Variables and functions */
 int /*<<< orphan*/  LOONGSON_LIO1_BASE ; 
 int /*<<< orphan*/  LOONGSON_PCIIO_BASE ; 
 int /*<<< orphan*/  LOONGSON_REG_BASE ; 
#define  MACH_DEXXON_GDIUM2F10 135 
#define  MACH_LEMOTE_FL2E 134 
#define  MACH_LEMOTE_FL2F 133 
#define  MACH_LEMOTE_LL2F 132 
#define  MACH_LEMOTE_ML2F7 131 
#define  MACH_LEMOTE_NAS 130 
#define  MACH_LEMOTE_YL2F89 129 
#define  MACH_LOONGSON_GENERIC 128 
 unsigned long* _loongson_uart_base ; 
 scalar_t__ ioremap_nocache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * loongson_uart_base ; 
 int mips_machtype ; 

void prom_init_loongson_uart_base(void)
{
	switch (mips_machtype) {
	case MACH_LOONGSON_GENERIC:
		/* The CPU provided serial port (CPU) */
		loongson_uart_base[0] = LOONGSON_REG_BASE + 0x1e0;
		break;
	case MACH_LEMOTE_FL2E:
		loongson_uart_base[0] = LOONGSON_PCIIO_BASE + 0x3f8;
		break;
	case MACH_LEMOTE_FL2F:
	case MACH_LEMOTE_LL2F:
		loongson_uart_base[0] = LOONGSON_PCIIO_BASE + 0x2f8;
		break;
	case MACH_LEMOTE_ML2F7:
	case MACH_LEMOTE_YL2F89:
	case MACH_DEXXON_GDIUM2F10:
	case MACH_LEMOTE_NAS:
	default:
		/* The CPU provided serial port (LPC) */
		loongson_uart_base[0] = LOONGSON_LIO1_BASE + 0x3f8;
		break;
	}

	_loongson_uart_base[0] =
		(unsigned long)ioremap_nocache(loongson_uart_base[0], 8);
}