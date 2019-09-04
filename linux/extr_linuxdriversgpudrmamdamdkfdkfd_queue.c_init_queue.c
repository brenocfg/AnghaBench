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
struct queue_properties {int dummy; } ;
struct queue {int /*<<< orphan*/  properties; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct queue* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct queue_properties const*,int) ; 

int init_queue(struct queue **q, const struct queue_properties *properties)
{
	struct queue *tmp_q;

	tmp_q = kzalloc(sizeof(*tmp_q), GFP_KERNEL);
	if (!tmp_q)
		return -ENOMEM;

	memcpy(&tmp_q->properties, properties, sizeof(*properties));

	*q = tmp_q;
	return 0;
}