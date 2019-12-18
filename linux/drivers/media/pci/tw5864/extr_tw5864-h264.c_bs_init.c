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
struct bs {int bits_left; void* ptr; void* buf_end; void* buf; } ;

/* Variables and functions */

__attribute__((used)) static void bs_init(struct bs *s, void *buf, int size)
{
	s->buf = buf;
	s->ptr = buf;
	s->buf_end = s->ptr + size;
	s->bits_left = 8;
}