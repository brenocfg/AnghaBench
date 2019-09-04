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
struct completion {int dummy; } ;
struct gpmi_nand_data {struct completion dma_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (struct completion*) ; 

__attribute__((used)) static void dma_irq_callback(void *param)
{
	struct gpmi_nand_data *this = param;
	struct completion *dma_c = &this->dma_done;

	complete(dma_c);
}