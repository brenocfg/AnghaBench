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
struct spi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct spi_controller {scalar_t__ bus_num; TYPE_1__ dev; } ;
struct spi_board_info {scalar_t__ bus_num; int /*<<< orphan*/  modalias; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct spi_device* spi_new_device (struct spi_controller*,struct spi_board_info*) ; 

__attribute__((used)) static void spi_match_controller_to_boardinfo(struct spi_controller *ctlr,
					      struct spi_board_info *bi)
{
	struct spi_device *dev;

	if (ctlr->bus_num != bi->bus_num)
		return;

	dev = spi_new_device(ctlr, bi);
	if (!dev)
		dev_err(ctlr->dev.parent, "can't create new device for %s\n",
			bi->modalias);
}