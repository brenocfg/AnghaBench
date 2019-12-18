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
struct komeda_format_caps_table {int /*<<< orphan*/  n_formats; int /*<<< orphan*/  format_mod_supported; int /*<<< orphan*/  format_caps; } ;
struct komeda_dev {struct komeda_format_caps_table fmt_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d71_format_caps_table ; 
 int /*<<< orphan*/  d71_format_mod_supported ; 

__attribute__((used)) static void d71_init_fmt_tbl(struct komeda_dev *mdev)
{
	struct komeda_format_caps_table *table = &mdev->fmt_tbl;

	table->format_caps = d71_format_caps_table;
	table->format_mod_supported = d71_format_mod_supported;
	table->n_formats = ARRAY_SIZE(d71_format_caps_table);
}