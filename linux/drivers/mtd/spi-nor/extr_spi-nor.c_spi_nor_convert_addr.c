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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* convert_addr ) (struct spi_nor*,int /*<<< orphan*/ ) ;} ;
struct spi_nor {TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct spi_nor*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 spi_nor_convert_addr(struct spi_nor *nor, loff_t addr)
{
	if (!nor->params.convert_addr)
		return addr;

	return nor->params.convert_addr(nor, addr);
}