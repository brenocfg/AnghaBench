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
 int EFAULT ; 
 int /*<<< orphan*/  isdigit (char) ; 
 scalar_t__ kstrtoul (char*,int,unsigned long*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int qat_uclo_parse_num(char *str, unsigned int *num)
{
	char buf[16] = {0};
	unsigned long ae = 0;
	int i;

	strncpy(buf, str, 15);
	for (i = 0; i < 16; i++) {
		if (!isdigit(buf[i])) {
			buf[i] = '\0';
			break;
		}
	}
	if ((kstrtoul(buf, 10, &ae)))
		return -EFAULT;

	*num = (unsigned int)ae;
	return 0;
}