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
struct ar9170 {int /*<<< orphan*/  state_lock; } ;
typedef  enum carl9170_device_state { ____Placeholder_carl9170_device_state } carl9170_device_state ;

/* Variables and functions */
 int /*<<< orphan*/  __carl9170_set_state (struct ar9170*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void carl9170_set_state(struct ar9170 *ar,
	enum carl9170_device_state newstate)
{
	unsigned long flags;

	spin_lock_irqsave(&ar->state_lock, flags);
	__carl9170_set_state(ar, newstate);
	spin_unlock_irqrestore(&ar->state_lock, flags);
}