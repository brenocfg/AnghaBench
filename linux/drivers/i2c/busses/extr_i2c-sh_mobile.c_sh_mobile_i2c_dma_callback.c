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
struct sh_mobile_i2c_data {int stop_after_dma; TYPE_1__* msg; int /*<<< orphan*/  pos; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICIC ; 
 int ICIC_RDMAE ; 
 int ICIC_TDMAE ; 
 int /*<<< orphan*/  iic_set_clr (struct sh_mobile_i2c_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sh_mobile_i2c_dma_unmap (struct sh_mobile_i2c_data*) ; 

__attribute__((used)) static void sh_mobile_i2c_dma_callback(void *data)
{
	struct sh_mobile_i2c_data *pd = data;

	sh_mobile_i2c_dma_unmap(pd);
	pd->pos = pd->msg->len;
	pd->stop_after_dma = true;

	iic_set_clr(pd, ICIC, 0, ICIC_TDMAE | ICIC_RDMAE);
}