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
typedef  int /*<<< orphan*/  t ;
struct kfifo {int dummy; } ;
struct ab_task {int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int kfifo_out_peek (struct kfifo*,struct ab_task**,int) ; 

__attribute__((used)) static bool qs_have_work(struct kfifo *qs, size_t num)
{
	size_t i;
	struct ab_task *t;
	int ret;

	for (i = 0; i < num; i++, qs++) {
		ret = kfifo_out_peek(qs, &t, sizeof(t));
		if (ret && (t->result != -EINPROGRESS))
			return true;
	}
	return false;
}