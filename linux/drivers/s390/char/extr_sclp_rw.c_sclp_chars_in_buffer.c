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
struct sclp_buffer {int char_sum; scalar_t__ current_length; int /*<<< orphan*/ * current_line; } ;

/* Variables and functions */

int
sclp_chars_in_buffer(struct sclp_buffer *buffer)
{
	int count;

	count = buffer->char_sum;
	if (buffer->current_line != NULL)
		count += buffer->current_length;
	return count;
}