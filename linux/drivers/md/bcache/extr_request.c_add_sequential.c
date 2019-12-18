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
struct task_struct {scalar_t__ sequential_io; int /*<<< orphan*/  sequential_io_avg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ewma_add (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_sequential(struct task_struct *t)
{
	ewma_add(t->sequential_io_avg,
		 t->sequential_io, 8, 0);

	t->sequential_io = 0;
}