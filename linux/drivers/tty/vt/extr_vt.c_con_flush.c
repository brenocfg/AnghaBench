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
typedef  int /*<<< orphan*/  u16 ;
struct vc_data {int /*<<< orphan*/  vc_y; TYPE_1__* vc_sw; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* con_putcs ) (struct vc_data*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct vc_data*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void con_flush(struct vc_data *vc, unsigned long draw_from,
		unsigned long draw_to, int *draw_x)
{
	if (*draw_x < 0)
		return;

	vc->vc_sw->con_putcs(vc, (u16 *)draw_from,
			(u16 *)draw_to - (u16 *)draw_from, vc->vc_y, *draw_x);
	*draw_x = -1;
}