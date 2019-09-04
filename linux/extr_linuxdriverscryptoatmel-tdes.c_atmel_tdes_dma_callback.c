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
struct atmel_tdes_dev {int /*<<< orphan*/  done_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atmel_tdes_dma_callback(void *data)
{
	struct atmel_tdes_dev *dd = data;

	/* dma_lch_out - completed */
	tasklet_schedule(&dd->done_task);
}