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
typedef  unsigned int u8 ;
struct b53_device {int dummy; } ;

/* Variables and functions */
 unsigned int ARLTBL_RW ; 
 unsigned int ARLTBL_START_DONE ; 
 int /*<<< orphan*/  B53_ARLIO_PAGE ; 
 int /*<<< orphan*/  B53_ARLTBL_RW_CTRL ; 
 int EINVAL ; 
 int b53_arl_op_wait (struct b53_device*) ; 
 int /*<<< orphan*/  b53_read8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  b53_write8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int b53_arl_rw_op(struct b53_device *dev, unsigned int op)
{
	u8 reg;

	if (op > ARLTBL_RW)
		return -EINVAL;

	b53_read8(dev, B53_ARLIO_PAGE, B53_ARLTBL_RW_CTRL, &reg);
	reg |= ARLTBL_START_DONE;
	if (op)
		reg |= ARLTBL_RW;
	else
		reg &= ~ARLTBL_RW;
	b53_write8(dev, B53_ARLIO_PAGE, B53_ARLTBL_RW_CTRL, reg);

	return b53_arl_op_wait(dev);
}