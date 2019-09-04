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
struct stk1160 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stk1160_cancel_isoc (struct stk1160*) ; 
 int /*<<< orphan*/  stk1160_free_isoc (struct stk1160*) ; 

void stk1160_uninit_isoc(struct stk1160 *dev)
{
	stk1160_cancel_isoc(dev);
	stk1160_free_isoc(dev);
}