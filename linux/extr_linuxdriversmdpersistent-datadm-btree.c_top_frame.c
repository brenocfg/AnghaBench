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
struct frame {int dummy; } ;
struct del_stack {scalar_t__ top; struct frame* spine; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int EINVAL ; 

__attribute__((used)) static int top_frame(struct del_stack *s, struct frame **f)
{
	if (s->top < 0) {
		DMERR("btree deletion stack empty");
		return -EINVAL;
	}

	*f = s->spine + s->top;

	return 0;
}