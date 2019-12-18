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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_notice (char*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qed_dbg_print_feature(u8 *p_text_buf, u32 text_size)
{
	u32 i, precision = 80;

	if (!p_text_buf)
		return;

	pr_notice("\n%.*s", precision, p_text_buf);
	for (i = precision; i < text_size; i += precision)
		pr_cont("%.*s", precision, p_text_buf + i);
	pr_cont("\n");
}