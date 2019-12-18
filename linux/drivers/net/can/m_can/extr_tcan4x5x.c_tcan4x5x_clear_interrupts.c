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
struct m_can_classdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCAN4X5X_CLEAR_ALL_INT ; 
 int /*<<< orphan*/  TCAN4X5X_ENABLE_MCAN_INT ; 
 int /*<<< orphan*/  TCAN4X5X_ERROR_STATUS ; 
 int /*<<< orphan*/  TCAN4X5X_INT_FLAGS ; 
 int /*<<< orphan*/  TCAN4X5X_MCAN_INT_REG ; 
 int /*<<< orphan*/  TCAN4X5X_STATUS ; 
 int tcan4x5x_write_tcan_reg (struct m_can_classdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcan4x5x_clear_interrupts(struct m_can_classdev *cdev)
{
	int ret;

	ret = tcan4x5x_write_tcan_reg(cdev, TCAN4X5X_STATUS,
				      TCAN4X5X_CLEAR_ALL_INT);
	if (ret)
		return ret;

	ret = tcan4x5x_write_tcan_reg(cdev, TCAN4X5X_MCAN_INT_REG,
				      TCAN4X5X_ENABLE_MCAN_INT);
	if (ret)
		return ret;

	ret = tcan4x5x_write_tcan_reg(cdev, TCAN4X5X_INT_FLAGS,
				      TCAN4X5X_CLEAR_ALL_INT);
	if (ret)
		return ret;

	ret = tcan4x5x_write_tcan_reg(cdev, TCAN4X5X_ERROR_STATUS,
				      TCAN4X5X_CLEAR_ALL_INT);
	if (ret)
		return ret;

	return ret;
}