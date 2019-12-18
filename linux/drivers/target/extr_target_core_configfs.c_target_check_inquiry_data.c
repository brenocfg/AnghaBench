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
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static ssize_t target_check_inquiry_data(char *buf)
{
	size_t len;
	int i;

	len = strlen(buf);

	/*
	 * SPC 4.3.1:
	 * ASCII data fields shall contain only ASCII printable characters
	 * (i.e., code values 20h to 7Eh) and may be terminated with one or
	 * more ASCII null (00h) characters.
	 */
	for (i = 0; i < len; i++) {
		if (buf[i] < 0x20 || buf[i] > 0x7E) {
			pr_err("Emulated T10 Inquiry Data contains non-ASCII-printable characters\n");
			return -EINVAL;
		}
	}

	return len;
}