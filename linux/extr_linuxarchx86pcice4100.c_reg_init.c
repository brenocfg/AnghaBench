#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
struct sim_dev_reg {TYPE_1__ sim_reg; int /*<<< orphan*/  reg; int /*<<< orphan*/  dev_func; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* read ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_2__ pci_direct_conf1 ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reg_init(struct sim_dev_reg *reg)
{
	pci_direct_conf1.read(0, 1, reg->dev_func, reg->reg, 4,
			      &reg->sim_reg.value);
}