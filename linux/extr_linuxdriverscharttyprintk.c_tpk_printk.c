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
 int TPK_STR_SIZE ; 
 char* tpk_buffer ; 
 int tpk_curr ; 
 int /*<<< orphan*/  tpk_flush () ; 

__attribute__((used)) static int tpk_printk(const unsigned char *buf, int count)
{
	int i = tpk_curr;

	if (buf == NULL) {
		tpk_flush();
		return i;
	}

	for (i = 0; i < count; i++) {
		if (tpk_curr >= TPK_STR_SIZE) {
			/* end of tmp buffer reached: cut the message in two */
			tpk_buffer[tpk_curr++] = '\\';
			tpk_flush();
		}

		switch (buf[i]) {
		case '\r':
			tpk_flush();
			if ((i + 1) < count && buf[i + 1] == '\n')
				i++;
			break;
		case '\n':
			tpk_flush();
			break;
		default:
			tpk_buffer[tpk_curr++] = buf[i];
			break;
		}
	}

	return count;
}