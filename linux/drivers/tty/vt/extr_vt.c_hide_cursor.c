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
struct vc_data {TYPE_1__* vc_sw; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* con_cursor ) (struct vc_data*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ERASE ; 
 int /*<<< orphan*/  clear_selection () ; 
 int /*<<< orphan*/  hide_softcursor (struct vc_data*) ; 
 struct vc_data* sel_cons ; 
 int /*<<< orphan*/  stub1 (struct vc_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hide_cursor(struct vc_data *vc)
{
	if (vc == sel_cons)
		clear_selection();
	vc->vc_sw->con_cursor(vc, CM_ERASE);
	hide_softcursor(vc);
}