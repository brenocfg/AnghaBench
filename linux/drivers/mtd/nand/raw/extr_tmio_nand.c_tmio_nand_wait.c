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
struct tmio_nand {TYPE_1__* dev; scalar_t__ fcr; int /*<<< orphan*/  comp; } ;
struct nand_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ FCR_IMR ; 
 scalar_t__ FCR_ISR ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (long) ; 
 struct tmio_nand* mtd_to_tmio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_status_op (struct nand_chip*,int*) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmio_iowrite8 (int,scalar_t__) ; 
 int /*<<< orphan*/  tmio_nand_dev_ready (struct nand_chip*) ; 
 scalar_t__ unlikely (int) ; 
 long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tmio_nand_wait(struct nand_chip *nand_chip)
{
	struct tmio_nand *tmio = mtd_to_tmio(nand_to_mtd(nand_chip));
	long timeout;
	u8 status;

	/* enable RDYREQ interrupt */

	tmio_iowrite8(0x0f, tmio->fcr + FCR_ISR);
	reinit_completion(&tmio->comp);
	tmio_iowrite8(0x81, tmio->fcr + FCR_IMR);

	timeout = 400;
	timeout = wait_for_completion_timeout(&tmio->comp,
					      msecs_to_jiffies(timeout));

	if (unlikely(!tmio_nand_dev_ready(nand_chip))) {
		tmio_iowrite8(0x00, tmio->fcr + FCR_IMR);
		dev_warn(&tmio->dev->dev, "still busy after 400 ms\n");

	} else if (unlikely(!timeout)) {
		tmio_iowrite8(0x00, tmio->fcr + FCR_IMR);
		dev_warn(&tmio->dev->dev, "timeout waiting for interrupt\n");
	}

	nand_status_op(nand_chip, &status);
	return status;
}