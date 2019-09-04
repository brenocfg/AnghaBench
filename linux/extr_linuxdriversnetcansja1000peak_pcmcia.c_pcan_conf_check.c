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
struct pcmcia_device {int io_lines; TYPE_1__** resource; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 int pcmcia_request_io (struct pcmcia_device*) ; 

__attribute__((used)) static int pcan_conf_check(struct pcmcia_device *pdev, void *priv_data)
{
	pdev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	pdev->resource[0]->flags |= IO_DATA_PATH_WIDTH_8; /* only */
	pdev->io_lines = 10;

	/* This reserves IO space but doesn't actually enable it */
	return pcmcia_request_io(pdev);
}