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
struct hsi_msg {int /*<<< orphan*/  sgt; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hsi_msg*) ; 
 struct hsi_msg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int sg_alloc_table (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct hsi_msg *hsi_alloc_msg(unsigned int nents, gfp_t flags)
{
	struct hsi_msg *msg;
	int err;

	msg = kzalloc(sizeof(*msg), flags);
	if (!msg)
		return NULL;

	if (!nents)
		return msg;

	err = sg_alloc_table(&msg->sgt, nents, flags);
	if (unlikely(err)) {
		kfree(msg);
		msg = NULL;
	}

	return msg;
}