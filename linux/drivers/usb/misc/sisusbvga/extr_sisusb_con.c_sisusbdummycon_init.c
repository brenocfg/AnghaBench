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
struct vc_data {int vc_can_do_color; int vc_cols; int vc_rows; } ;

/* Variables and functions */
 int /*<<< orphan*/  vc_resize (struct vc_data*,int,int) ; 

__attribute__((used)) static void sisusbdummycon_init(struct vc_data *vc, int init)
{
    vc->vc_can_do_color = 1;
    if (init) {
	vc->vc_cols = 80;
	vc->vc_rows = 25;
    } else
	vc_resize(vc, 80, 25);
}