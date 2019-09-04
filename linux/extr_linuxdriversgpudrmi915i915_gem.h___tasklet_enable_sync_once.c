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
struct tasklet_struct {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (struct tasklet_struct*) ; 

__attribute__((used)) static inline void __tasklet_enable_sync_once(struct tasklet_struct *t)
{
	if (atomic_dec_return(&t->count) == 0)
		tasklet_kill(t);
}