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
typedef  int u8 ;
struct r852_device {scalar_t__ dma_error; } ;
struct TYPE_2__ {scalar_t__ (* dev_ready ) (struct nand_chip*) ;} ;
struct nand_chip {TYPE_1__ legacy; } ;

/* Variables and functions */
 int NAND_STATUS_FAIL ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 struct r852_device* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_status_op (struct nand_chip*,int*) ; 
 scalar_t__ stub1 (struct nand_chip*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int r852_wait(struct nand_chip *chip)
{
	struct r852_device *dev = nand_get_controller_data(chip);

	unsigned long timeout;
	u8 status;

	timeout = jiffies + msecs_to_jiffies(400);

	while (time_before(jiffies, timeout))
		if (chip->legacy.dev_ready(chip))
			break;

	nand_status_op(chip, &status);

	/* Unfortunelly, no way to send detailed error status... */
	if (dev->dma_error) {
		status |= NAND_STATUS_FAIL;
		dev->dma_error = 0;
	}
	return status;
}