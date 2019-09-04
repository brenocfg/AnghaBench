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

/* Variables and functions */
 int /*<<< orphan*/  strncpy (char*,void*,int) ; 
 int strnlen (char*,int) ; 

__attribute__((used)) static int strncpy_chunk_from_user(unsigned long from, int len, void *arg)
{
	char **to_ptr = arg, *to = *to_ptr;
	int n;

	strncpy(to, (void *) from, len);
	n = strnlen(to, len);
	*to_ptr += n;

	if (n < len)
	        return 1;
	return 0;
}