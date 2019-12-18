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
struct xadc {TYPE_1__* ops; } ;
struct TYPE_2__ {unsigned long (* get_dclk_rate ) (struct xadc*) ;} ;

/* Variables and functions */
 unsigned long stub1 (struct xadc*) ; 

__attribute__((used)) static unsigned long xadc_get_dclk_rate(struct xadc *xadc)
{
	return xadc->ops->get_dclk_rate(xadc);
}