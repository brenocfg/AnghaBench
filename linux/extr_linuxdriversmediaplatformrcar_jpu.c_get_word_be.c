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
struct jpeg_buffer {int end; int curr; } ;

/* Variables and functions */
 unsigned int get_unaligned_be16 (int) ; 

__attribute__((used)) static int get_word_be(struct jpeg_buffer *buf, unsigned int *word)
{
	if (buf->end - buf->curr < 2)
		return -1;

	*word = get_unaligned_be16(buf->curr);
	buf->curr += 2;

	return 0;
}