#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sgl; } ;
struct hsi_msg {TYPE_1__ sgt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hsi_msg* hsi_alloc_msg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsi_free_msg (struct hsi_msg*) ; 
 void* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemleak_ignore (void*) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ ,void*,unsigned int) ; 

__attribute__((used)) static inline struct hsi_msg *hsc_msg_alloc(unsigned int alloc_size)
{
	struct hsi_msg *msg;
	void *buf;

	msg = hsi_alloc_msg(1, GFP_KERNEL);
	if (!msg)
		goto out;
	buf = kmalloc(alloc_size, GFP_KERNEL);
	if (!buf) {
		hsi_free_msg(msg);
		goto out;
	}
	sg_init_one(msg->sgt.sgl, buf, alloc_size);
	/* Ignore false positive, due to sg pointer handling */
	kmemleak_ignore(buf);

	return msg;
out:
	return NULL;
}