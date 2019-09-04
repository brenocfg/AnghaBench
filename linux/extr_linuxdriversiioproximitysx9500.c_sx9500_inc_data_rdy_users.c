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
struct sx9500_data {int /*<<< orphan*/  data_rdy_users; } ;

/* Variables and functions */
 int /*<<< orphan*/  SX9500_CONVDONE_IRQ ; 
 int /*<<< orphan*/  SX9500_REG_IRQ_MSK ; 
 int sx9500_inc_users (struct sx9500_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sx9500_inc_data_rdy_users(struct sx9500_data *data)
{
	return sx9500_inc_users(data, &data->data_rdy_users,
				SX9500_REG_IRQ_MSK, SX9500_CONVDONE_IRQ);
}