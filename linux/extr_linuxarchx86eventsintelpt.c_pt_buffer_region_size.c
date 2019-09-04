#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_buffer {size_t cur_idx; TYPE_2__* cur; } ;
struct TYPE_4__ {TYPE_1__* table; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 size_t sizes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t pt_buffer_region_size(struct pt_buffer *buf)
{
	return sizes(buf->cur->table[buf->cur_idx].size);
}