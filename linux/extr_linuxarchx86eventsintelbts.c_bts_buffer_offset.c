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
struct bts_buffer {TYPE_1__* buf; } ;
struct TYPE_2__ {unsigned long offset; unsigned long displacement; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long bts_buffer_offset(struct bts_buffer *buf, unsigned int idx)
{
	return buf->buf[idx].offset + buf->buf[idx].displacement;
}