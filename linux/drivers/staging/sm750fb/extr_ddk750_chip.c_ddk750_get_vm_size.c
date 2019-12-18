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
 int /*<<< orphan*/  MISC_CTRL ; 
#define  MISC_CTRL_LOCALMEM_SIZE_16M 131 
#define  MISC_CTRL_LOCALMEM_SIZE_32M 130 
#define  MISC_CTRL_LOCALMEM_SIZE_64M 129 
#define  MISC_CTRL_LOCALMEM_SIZE_8M 128 
 unsigned int MISC_CTRL_LOCALMEM_SIZE_MASK ; 
 int /*<<< orphan*/  MODE0_GATE ; 
 unsigned int MODE0_GATE_GPIO ; 
 scalar_t__ SM750LE ; 
 unsigned int SZ_16M ; 
 unsigned int SZ_32M ; 
 unsigned int SZ_64M ; 
 unsigned int SZ_8M ; 
 unsigned int peek32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ sm750_get_chip_type () ; 

unsigned int ddk750_get_vm_size(void)
{
	unsigned int reg;
	unsigned int data;

	/* sm750le only use 64 mb memory*/
	if (sm750_get_chip_type() == SM750LE)
		return SZ_64M;

	/* for 750,always use power mode0*/
	reg = peek32(MODE0_GATE);
	reg |= MODE0_GATE_GPIO;
	poke32(MODE0_GATE, reg);

	/* get frame buffer size from GPIO */
	reg = peek32(MISC_CTRL) & MISC_CTRL_LOCALMEM_SIZE_MASK;
	switch (reg) {
	case MISC_CTRL_LOCALMEM_SIZE_8M:
		data = SZ_8M;  break; /* 8  Mega byte */
	case MISC_CTRL_LOCALMEM_SIZE_16M:
		data = SZ_16M; break; /* 16 Mega byte */
	case MISC_CTRL_LOCALMEM_SIZE_32M:
		data = SZ_32M; break; /* 32 Mega byte */
	case MISC_CTRL_LOCALMEM_SIZE_64M:
		data = SZ_64M; break; /* 64 Mega byte */
	default:
		data = 0;
		break;
	}
	return data;
}