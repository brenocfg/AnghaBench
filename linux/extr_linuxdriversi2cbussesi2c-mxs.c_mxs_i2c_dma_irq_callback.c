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
struct mxs_i2c_dev {int /*<<< orphan*/  cmd_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxs_i2c_dma_finish (struct mxs_i2c_dev*) ; 

__attribute__((used)) static void mxs_i2c_dma_irq_callback(void *param)
{
	struct mxs_i2c_dev *i2c = param;

	complete(&i2c->cmd_complete);
	mxs_i2c_dma_finish(i2c);
}