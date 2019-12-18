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
struct slgt_info {scalar_t__ rbuf_fill_count; scalar_t__ rbuf_fill_index; scalar_t__ rbuf_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_rbufs (struct slgt_info*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void reset_rbufs(struct slgt_info *info)
{
	free_rbufs(info, 0, info->rbuf_count - 1);
	info->rbuf_fill_index = 0;
	info->rbuf_fill_count = 0;
}