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
struct etmv4_reg {int /*<<< orphan*/  addr; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl_relaxed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_smp_cross_read(void *data)
{
	struct etmv4_reg *reg = data;

	reg->data = readl_relaxed(reg->addr);
}