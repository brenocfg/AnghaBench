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
struct ata_queued_cmd {TYPE_1__* dev; int /*<<< orphan*/  ap; } ;
struct TYPE_2__ {int /*<<< orphan*/  pio_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_bmdma_stop (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  ns87415_set_mode (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ns87415_bmdma_stop(struct ata_queued_cmd *qc)
{
	ata_bmdma_stop(qc);
	ns87415_set_mode(qc->ap, qc->dev, qc->dev->pio_mode);
}