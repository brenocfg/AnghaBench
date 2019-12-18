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
 int /*<<< orphan*/  ioread16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 sh_msiof_read(struct sh_msiof_spi_priv *p, int reg_offs)
{
	switch (reg_offs) {
	case TSCR:
	case RSCR:
		return ioread16(p->mapbase + reg_offs);
	default:
		return ioread32(p->mapbase + reg_offs);
	}
}