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
struct vcnl4000_data {int /*<<< orphan*/  vcnl4200_ps; } ;

/* Variables and functions */
 int vcnl4200_measure (struct vcnl4000_data*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int vcnl4200_measure_proximity(struct vcnl4000_data *data, int *val)
{
	return vcnl4200_measure(data, &data->vcnl4200_ps, val);
}