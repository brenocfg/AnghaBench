#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct param_dma_output {int dummy; } ;
struct fimc_is {int dummy; } ;
struct TYPE_3__ {struct param_dma_output dma2_output; } ;
struct TYPE_4__ {TYPE_1__ isp; } ;

/* Variables and functions */
 TYPE_2__* __get_curr_is_config (struct fimc_is*) ; 

__attribute__((used)) static inline struct param_dma_output *__get_isp_dma2(struct fimc_is *is)
{
	return &__get_curr_is_config(is)->isp.dma2_output;
}