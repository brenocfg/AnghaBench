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
typedef  int /*<<< orphan*/  uint16_t ;
struct xadc {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int _xadc_update_adc_reg (struct xadc*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xadc_update_adc_reg(struct xadc *xadc, unsigned int reg,
	uint16_t mask, uint16_t val)
{
	int ret;

	mutex_lock(&xadc->mutex);
	ret = _xadc_update_adc_reg(xadc, reg, mask, val);
	mutex_unlock(&xadc->mutex);

	return ret;
}