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

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hsi_msg*) ; 
 int /*<<< orphan*/  sg_free_table (int /*<<< orphan*/ *) ; 

void hsi_free_msg(struct hsi_msg *msg)
{
	if (!msg)
		return;
	sg_free_table(&msg->sgt);
	kfree(msg);
}