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
struct sx9500_data {int /*<<< orphan*/  close_far_users; } ;

/* Variables and functions */
 int SX9500_CLOSE_IRQ ; 
 int SX9500_FAR_IRQ ; 
 int /*<<< orphan*/  SX9500_REG_IRQ_MSK ; 
 int sx9500_dec_users (struct sx9500_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sx9500_dec_close_far_users(struct sx9500_data *data)
{
	return sx9500_dec_users(data, &data->close_far_users,
				SX9500_REG_IRQ_MSK,
				SX9500_CLOSE_IRQ | SX9500_FAR_IRQ);
}