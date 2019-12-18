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
 int /*<<< orphan*/  hsi_free_msg (struct hsi_msg*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_virt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hsc_msg_free(struct hsi_msg *msg)
{
	kfree(sg_virt(msg->sgt.sgl));
	hsi_free_msg(msg);
}