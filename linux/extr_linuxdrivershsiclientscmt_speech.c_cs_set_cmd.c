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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  sgl; } ;
struct hsi_msg {TYPE_1__ sgt; } ;

/* Variables and functions */
 int /*<<< orphan*/ * sg_virt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cs_set_cmd(struct hsi_msg *msg, u32 cmd)
{
	u32 *data = sg_virt(msg->sgt.sgl);
	*data = cmd;
}