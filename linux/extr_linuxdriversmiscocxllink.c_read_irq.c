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
typedef  int u64 ;
struct spa {int /*<<< orphan*/  reg_pe_handle; int /*<<< orphan*/  reg_dar; int /*<<< orphan*/  reg_dsisr; } ;

/* Variables and functions */
 int SPA_PE_MASK ; 
 int in_be64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_irq(struct spa *spa, u64 *dsisr, u64 *dar, u64 *pe)
{
	u64 reg;

	*dsisr = in_be64(spa->reg_dsisr);
	*dar = in_be64(spa->reg_dar);
	reg = in_be64(spa->reg_pe_handle);
	*pe = reg & SPA_PE_MASK;
}