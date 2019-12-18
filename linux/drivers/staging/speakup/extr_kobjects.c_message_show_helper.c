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
typedef  int ssize_t ;
typedef  enum msg_index_t { ____Placeholder_msg_index_t } msg_index_t ;

/* Variables and functions */
 size_t PAGE_SIZE ; 
 int scnprintf (char*,size_t,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spk_msg_get (int) ; 

__attribute__((used)) static ssize_t message_show_helper(char *buf, enum msg_index_t first,
				   enum msg_index_t last)
{
	size_t bufsize = PAGE_SIZE;
	char *buf_pointer = buf;
	int printed;
	enum msg_index_t cursor;
	int index = 0;
	*buf_pointer = '\0'; /* buf_pointer always looking at a NUL byte. */

	for (cursor = first; cursor <= last; cursor++, index++) {
		if (bufsize <= 1)
			break;
		printed = scnprintf(buf_pointer, bufsize, "%d\t%s\n",
				    index, spk_msg_get(cursor));
		buf_pointer += printed;
		bufsize -= printed;
	}

	return buf_pointer - buf;
}