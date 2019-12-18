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
struct etnaviv_gpu {int dummy; } ;
struct etnaviv_dump_registers {int /*<<< orphan*/  value; int /*<<< orphan*/  reg; } ;
struct core_dump_iterator {struct etnaviv_dump_registers* data; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ETDUMP_BUF_REG ; 
 int /*<<< orphan*/  etnaviv_core_dump_header (struct core_dump_iterator*,int /*<<< orphan*/ ,struct etnaviv_dump_registers*) ; 
 int /*<<< orphan*/ * etnaviv_dump_registers ; 
 int /*<<< orphan*/  gpu_read (struct etnaviv_gpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void etnaviv_core_dump_registers(struct core_dump_iterator *iter,
	struct etnaviv_gpu *gpu)
{
	struct etnaviv_dump_registers *reg = iter->data;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(etnaviv_dump_registers); i++, reg++) {
		reg->reg = etnaviv_dump_registers[i];
		reg->value = gpu_read(gpu, etnaviv_dump_registers[i]);
	}

	etnaviv_core_dump_header(iter, ETDUMP_BUF_REG, reg);
}