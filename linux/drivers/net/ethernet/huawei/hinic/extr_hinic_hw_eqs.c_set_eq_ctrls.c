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
struct hinic_eq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_ctrl0 (struct hinic_eq*) ; 
 int /*<<< orphan*/  set_ctrl1 (struct hinic_eq*) ; 

__attribute__((used)) static void set_eq_ctrls(struct hinic_eq *eq)
{
	set_ctrl0(eq);
	set_ctrl1(eq);
}