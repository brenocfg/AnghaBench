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
struct qeth_cmd_buffer {struct qeth_cmd_buffer* data; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct qeth_cmd_buffer*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void qeth_put_cmd(struct qeth_cmd_buffer *iob)
{
	if (refcount_dec_and_test(&iob->ref_count)) {
		kfree(iob->data);
		kfree(iob);
	}
}