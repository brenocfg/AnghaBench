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
struct slgt_info {int /*<<< orphan*/ * flag_buf; int /*<<< orphan*/ * tmp_rbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_tmp_rbuf(struct slgt_info *info)
{
	kfree(info->tmp_rbuf);
	info->tmp_rbuf = NULL;
	kfree(info->flag_buf);
	info->flag_buf = NULL;
}