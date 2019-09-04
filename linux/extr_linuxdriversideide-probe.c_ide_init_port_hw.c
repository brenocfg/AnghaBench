#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ide_hw {int /*<<< orphan*/  config; scalar_t__ dev; scalar_t__ parent; int /*<<< orphan*/  irq; int /*<<< orphan*/  io_ports; } ;
struct TYPE_4__ {scalar_t__ parent; } ;
struct TYPE_5__ {int /*<<< orphan*/  config_data; TYPE_1__ gendev; scalar_t__ dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  io_ports; } ;
typedef  TYPE_2__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ide_init_port_hw(ide_hwif_t *hwif, struct ide_hw *hw)
{
	memcpy(&hwif->io_ports, &hw->io_ports, sizeof(hwif->io_ports));
	hwif->irq = hw->irq;
	hwif->dev = hw->dev;
	hwif->gendev.parent = hw->parent ? hw->parent : hw->dev;
	hwif->config_data = hw->config;
}