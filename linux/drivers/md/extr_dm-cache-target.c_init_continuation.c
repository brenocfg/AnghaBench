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
struct continuation {scalar_t__ input; int /*<<< orphan*/  ws; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,void (*) (struct work_struct*)) ; 

__attribute__((used)) static inline void init_continuation(struct continuation *k,
				     void (*fn)(struct work_struct *))
{
	INIT_WORK(&k->ws, fn);
	k->input = 0;
}