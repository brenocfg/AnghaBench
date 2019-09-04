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
struct gpio {int id; int /*<<< orphan*/  en; } ;
typedef  enum sync_source { ____Placeholder_sync_source } sync_source ;

/* Variables and functions */
#define  GPIO_GENERIC_A 147 
#define  GPIO_GENERIC_B 146 
#define  GPIO_GENERIC_C 145 
#define  GPIO_GENERIC_D 144 
#define  GPIO_GENERIC_E 143 
#define  GPIO_GENERIC_F 142 
#define  GPIO_GSL_GENLOCK_CLOCK 141 
#define  GPIO_GSL_GENLOCK_VSYNC 140 
#define  GPIO_GSL_SWAPLOCK_A 139 
#define  GPIO_GSL_SWAPLOCK_B 138 
#define  GPIO_HPD_1 137 
#define  GPIO_HPD_2 136 
#define  GPIO_ID_GENERIC 135 
#define  GPIO_ID_GSL 134 
#define  GPIO_ID_HPD 133 
#define  GPIO_ID_SYNC 132 
#define  GPIO_SYNC_HSYNC_A 131 
#define  GPIO_SYNC_HSYNC_B 130 
#define  GPIO_SYNC_VSYNC_A 129 
#define  GPIO_SYNC_VSYNC_B 128 
 int SYNC_SOURCE_GSL_IO_GENLOCK_CLOCK ; 
 int SYNC_SOURCE_GSL_IO_GENLOCK_VSYNC ; 
 int SYNC_SOURCE_GSL_IO_SWAPLOCK_A ; 
 int SYNC_SOURCE_GSL_IO_SWAPLOCK_B ; 
 int SYNC_SOURCE_IO_GENERIC_A ; 
 int SYNC_SOURCE_IO_GENERIC_B ; 
 int SYNC_SOURCE_IO_GENERIC_C ; 
 int SYNC_SOURCE_IO_GENERIC_D ; 
 int SYNC_SOURCE_IO_GENERIC_E ; 
 int SYNC_SOURCE_IO_GENERIC_F ; 
 int SYNC_SOURCE_IO_HPD1 ; 
 int SYNC_SOURCE_IO_HPD2 ; 
 int SYNC_SOURCE_IO_HSYNC_A ; 
 int SYNC_SOURCE_IO_HSYNC_B ; 
 int SYNC_SOURCE_IO_VSYNC_A ; 
 int SYNC_SOURCE_IO_VSYNC_B ; 
 int SYNC_SOURCE_NONE ; 

enum sync_source dal_gpio_get_sync_source(
	const struct gpio *gpio)
{
	switch (gpio->id) {
	case GPIO_ID_GENERIC:
		switch (gpio->en) {
		case GPIO_GENERIC_A:
			return SYNC_SOURCE_IO_GENERIC_A;
		case GPIO_GENERIC_B:
			return SYNC_SOURCE_IO_GENERIC_B;
		case GPIO_GENERIC_C:
			return SYNC_SOURCE_IO_GENERIC_C;
		case GPIO_GENERIC_D:
			return SYNC_SOURCE_IO_GENERIC_D;
		case GPIO_GENERIC_E:
			return SYNC_SOURCE_IO_GENERIC_E;
		case GPIO_GENERIC_F:
			return SYNC_SOURCE_IO_GENERIC_F;
		default:
			return SYNC_SOURCE_NONE;
		}
	break;
	case GPIO_ID_SYNC:
		switch (gpio->en) {
		case GPIO_SYNC_HSYNC_A:
			return SYNC_SOURCE_IO_HSYNC_A;
		case GPIO_SYNC_VSYNC_A:
			return SYNC_SOURCE_IO_VSYNC_A;
		case GPIO_SYNC_HSYNC_B:
			return SYNC_SOURCE_IO_HSYNC_B;
		case GPIO_SYNC_VSYNC_B:
			return SYNC_SOURCE_IO_VSYNC_B;
		default:
			return SYNC_SOURCE_NONE;
		}
	break;
	case GPIO_ID_HPD:
		switch (gpio->en) {
		case GPIO_HPD_1:
			return SYNC_SOURCE_IO_HPD1;
		case GPIO_HPD_2:
			return SYNC_SOURCE_IO_HPD2;
		default:
			return SYNC_SOURCE_NONE;
		}
	break;
	case GPIO_ID_GSL:
		switch (gpio->en) {
		case GPIO_GSL_GENLOCK_CLOCK:
			return SYNC_SOURCE_GSL_IO_GENLOCK_CLOCK;
		case GPIO_GSL_GENLOCK_VSYNC:
			return SYNC_SOURCE_GSL_IO_GENLOCK_VSYNC;
		case GPIO_GSL_SWAPLOCK_A:
			return SYNC_SOURCE_GSL_IO_SWAPLOCK_A;
		case GPIO_GSL_SWAPLOCK_B:
			return SYNC_SOURCE_GSL_IO_SWAPLOCK_B;
		default:
			return SYNC_SOURCE_NONE;
		}
	break;
	default:
		return SYNC_SOURCE_NONE;
	}
}