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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int index; } ;
struct vsp1_rwpf {TYPE_1__ entity; } ;
struct vsp1_dl_body {int dummy; } ;

/* Variables and functions */
 int VI6_WPF_OFFSET ; 
 int /*<<< orphan*/  vsp1_dl_body_write (struct vsp1_dl_body*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void vsp1_wpf_write(struct vsp1_rwpf *wpf,
				  struct vsp1_dl_body *dlb, u32 reg, u32 data)
{
	vsp1_dl_body_write(dlb, reg + wpf->entity.index * VI6_WPF_OFFSET, data);
}