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
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  e1000_put_hw_semaphore_82573 (struct e1000_hw*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swflag_mutex ; 

__attribute__((used)) static void e1000_put_hw_semaphore_82574(struct e1000_hw *hw)
{
	e1000_put_hw_semaphore_82573(hw);
	mutex_unlock(&swflag_mutex);
}