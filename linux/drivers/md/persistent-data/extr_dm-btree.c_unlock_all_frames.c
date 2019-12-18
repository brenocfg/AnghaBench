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
struct frame {int /*<<< orphan*/  b; } ;
struct del_stack {int /*<<< orphan*/  tm; int /*<<< orphan*/  top; struct frame* spine; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_tm_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unprocessed_frames (struct del_stack*) ; 

__attribute__((used)) static void unlock_all_frames(struct del_stack *s)
{
	struct frame *f;

	while (unprocessed_frames(s)) {
		f = s->spine + s->top--;
		dm_tm_unlock(s->tm, f->b);
	}
}