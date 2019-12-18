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
 unsigned char DECIMAL ; 
 unsigned char HEX ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,unsigned int) ; 
 int strlen_semi (char*) ; 
 char* strstr (char const*,char const*) ; 

int extract_param(
	const char *in_buf,
	const char *pattern,
	unsigned int max_length,
	char *out_buf,
	unsigned char *type)
{
	char *ptr;
	int len;

	if (!in_buf || !pattern || !out_buf || !type)
		return -1;

	ptr = strstr(in_buf, pattern);
	if (!ptr)
		return -1;

	ptr = strstr(ptr, "=");
	if (!ptr)
		return -1;

	ptr += 1;
	if (*ptr == '0' && (*(ptr+1) == 'x' || *(ptr+1) == 'X')) {
		ptr += 2; /* skip 0x */
		*type = HEX;
	} else
		*type = DECIMAL;

	len = strlen_semi(ptr);
	if (len < 0)
		return -1;

	if (len >= max_length) {
		pr_err("Length of input: %d exceeds max_length:"
			" %d\n", len, max_length);
		return -1;
	}
	memcpy(out_buf, ptr, len);
	out_buf[len] = '\0';

	return 0;
}