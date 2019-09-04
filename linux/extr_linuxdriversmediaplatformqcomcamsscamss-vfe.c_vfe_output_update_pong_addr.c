#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct vfe_output {unsigned int wm_num; int /*<<< orphan*/ * wm_idx; TYPE_2__** buf; } ;
struct vfe_device {TYPE_1__* ops; } ;
struct TYPE_4__ {scalar_t__* addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* bus_reload_wm ) (struct vfe_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* wm_set_pong_addr ) (struct vfe_device*,int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct vfe_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct vfe_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vfe_output_update_pong_addr(struct vfe_device *vfe,
					struct vfe_output *output, u8 sync)
{
	u32 addr;
	unsigned int i;

	for (i = 0; i < output->wm_num; i++) {
		if (output->buf[1])
			addr = output->buf[1]->addr[i];
		else
			addr = 0;

		vfe->ops->wm_set_pong_addr(vfe, output->wm_idx[i], addr);
		if (sync)
			vfe->ops->bus_reload_wm(vfe, output->wm_idx[i]);
	}

}