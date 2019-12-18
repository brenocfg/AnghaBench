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
struct musb {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pre_root_reset_end ) (struct musb*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct musb*) ; 

__attribute__((used)) static inline void musb_platform_pre_root_reset_end(struct musb *musb)
{
	if (musb->ops->pre_root_reset_end)
		musb->ops->pre_root_reset_end(musb);
}