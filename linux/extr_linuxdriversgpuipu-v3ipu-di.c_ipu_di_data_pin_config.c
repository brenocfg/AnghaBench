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
struct ipu_di {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DI_DW_GEN (int) ; 
 int /*<<< orphan*/  DI_DW_SET (int,int) ; 
 int ipu_di_read (struct ipu_di*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_di_write (struct ipu_di*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipu_di_data_pin_config(struct ipu_di *di, int wave_gen, int di_pin,
		int set, int up, int down)
{
	u32 reg;

	reg = ipu_di_read(di, DI_DW_GEN(wave_gen));
	reg &= ~(0x3 << (di_pin * 2));
	reg |= set << (di_pin * 2);
	ipu_di_write(di, reg, DI_DW_GEN(wave_gen));

	ipu_di_write(di, (down << 16) | up, DI_DW_SET(wave_gen, set));
}