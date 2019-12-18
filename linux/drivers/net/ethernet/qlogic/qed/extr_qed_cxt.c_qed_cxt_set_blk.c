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
struct qed_ilt_cli_blk {scalar_t__ total_size; } ;

/* Variables and functions */

__attribute__((used)) static struct qed_ilt_cli_blk *qed_cxt_set_blk(struct qed_ilt_cli_blk *p_blk)
{
	p_blk->total_size = 0;
	return p_blk;
}