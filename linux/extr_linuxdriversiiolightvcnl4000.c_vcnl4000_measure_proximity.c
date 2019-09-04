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
struct vcnl4000_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCNL4000_PS_OD ; 
 int /*<<< orphan*/  VCNL4000_PS_RDY ; 
 int /*<<< orphan*/  VCNL4000_PS_RESULT_HI ; 
 int vcnl4000_measure (struct vcnl4000_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int vcnl4000_measure_proximity(struct vcnl4000_data *data, int *val)
{
	return vcnl4000_measure(data,
			VCNL4000_PS_OD, VCNL4000_PS_RDY,
			VCNL4000_PS_RESULT_HI, val);
}