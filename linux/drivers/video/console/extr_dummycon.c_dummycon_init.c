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
struct vc_data {int vc_can_do_color; int /*<<< orphan*/  vc_rows; int /*<<< orphan*/  vc_cols; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMMY_COLUMNS ; 
 int /*<<< orphan*/  DUMMY_ROWS ; 
 int /*<<< orphan*/  vc_resize (struct vc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dummycon_init(struct vc_data *vc, int init)
{
    vc->vc_can_do_color = 1;
    if (init) {
	vc->vc_cols = DUMMY_COLUMNS;
	vc->vc_rows = DUMMY_ROWS;
    } else
	vc_resize(vc, DUMMY_COLUMNS, DUMMY_ROWS);
}