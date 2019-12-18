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
typedef  int /*<<< orphan*/  u32 ;
struct sh_msiof_spi_priv {int /*<<< orphan*/  mapbase; } ;

/* Variables and functions */
#define  RSCR 129 
#define  TSCR 128 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_msiof_write(struct sh_msiof_spi_priv *p, int reg_offs,
			   u32 value)
{
	switch (reg_offs) {
	case TSCR:
	case RSCR:
		iowrite16(value, p->mapbase + reg_offs);
		break;
	default:
		iowrite32(value, p->mapbase + reg_offs);
		break;
	}
}