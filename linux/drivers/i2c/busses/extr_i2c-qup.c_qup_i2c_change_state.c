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
typedef  int /*<<< orphan*/  u32 ;
struct qup_i2c_dev {scalar_t__ base; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ QUP_STATE ; 
 scalar_t__ qup_i2c_poll_state (struct qup_i2c_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ qup_i2c_poll_state_valid (struct qup_i2c_dev*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int qup_i2c_change_state(struct qup_i2c_dev *qup, u32 state)
{
	if (qup_i2c_poll_state_valid(qup) != 0)
		return -EIO;

	writel(state, qup->base + QUP_STATE);

	if (qup_i2c_poll_state(qup, state) != 0)
		return -EIO;
	return 0;
}