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
struct vfe_output {unsigned int wm_num; int /*<<< orphan*/ * wm_idx; TYPE_1__** buf; scalar_t__ active_buf; } ;
struct vfe_device {TYPE_2__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* bus_reload_wm ) (struct vfe_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* wm_set_pong_addr ) (struct vfe_device*,int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* wm_set_ping_addr ) (struct vfe_device*,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_3__ {scalar_t__* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct vfe_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct vfe_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (struct vfe_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vfe_output_init_addrs(struct vfe_device *vfe,
				  struct vfe_output *output, u8 sync)
{
	u32 ping_addr;
	u32 pong_addr;
	unsigned int i;

	output->active_buf = 0;

	for (i = 0; i < output->wm_num; i++) {
		if (output->buf[0])
			ping_addr = output->buf[0]->addr[i];
		else
			ping_addr = 0;

		if (output->buf[1])
			pong_addr = output->buf[1]->addr[i];
		else
			pong_addr = ping_addr;

		vfe->ops->wm_set_ping_addr(vfe, output->wm_idx[i], ping_addr);
		vfe->ops->wm_set_pong_addr(vfe, output->wm_idx[i], pong_addr);
		if (sync)
			vfe->ops->bus_reload_wm(vfe, output->wm_idx[i]);
	}
}