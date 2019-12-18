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
struct saa7164_user_buffer {struct saa7164_user_buffer* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct saa7164_user_buffer*) ; 

void saa7164_buffer_dealloc_user(struct saa7164_user_buffer *buf)
{
	if (!buf)
		return;

	kfree(buf->data);
	buf->data = NULL;

	kfree(buf);
}