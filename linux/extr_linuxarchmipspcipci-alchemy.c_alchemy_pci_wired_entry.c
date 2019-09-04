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
struct alchemy_pci_context {int /*<<< orphan*/  last_elo1; int /*<<< orphan*/  last_elo0; TYPE_1__* pci_cfg_vm; int /*<<< orphan*/  wired_entry; } ;
struct TYPE_2__ {scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM_4K ; 
 int /*<<< orphan*/  add_wired_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_c0_wired () ; 

__attribute__((used)) static void alchemy_pci_wired_entry(struct alchemy_pci_context *ctx)
{
	ctx->wired_entry = read_c0_wired();
	add_wired_entry(0, 0, (unsigned long)ctx->pci_cfg_vm->addr, PM_4K);
	ctx->last_elo0 = ctx->last_elo1 = ~0;
}