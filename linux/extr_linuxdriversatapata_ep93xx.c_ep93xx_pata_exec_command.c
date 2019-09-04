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
struct ep93xx_pata_data {int dummy; } ;
struct ata_taskfile {int /*<<< orphan*/  command; } ;
struct ata_port {TYPE_1__* host; } ;
struct TYPE_2__ {struct ep93xx_pata_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDECTRL_ADDR_COMMAND ; 
 int /*<<< orphan*/  ata_sff_pause (struct ata_port*) ; 
 int /*<<< orphan*/  ep93xx_pata_write_reg (struct ep93xx_pata_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ep93xx_pata_exec_command(struct ata_port *ap,
				     const struct ata_taskfile *tf)
{
	struct ep93xx_pata_data *drv_data = ap->host->private_data;

	ep93xx_pata_write_reg(drv_data, tf->command,
			  IDECTRL_ADDR_COMMAND);
	ata_sff_pause(ap);
}