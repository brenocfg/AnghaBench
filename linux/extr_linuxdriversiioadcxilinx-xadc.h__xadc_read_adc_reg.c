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
typedef  int /*<<< orphan*/  uint16_t ;
struct xadc {TYPE_1__* ops; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int (* read ) (struct xadc*,unsigned int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int stub1 (struct xadc*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int _xadc_read_adc_reg(struct xadc *xadc, unsigned int reg,
	uint16_t *val)
{
	lockdep_assert_held(&xadc->mutex);
	return xadc->ops->read(xadc, reg, val);
}