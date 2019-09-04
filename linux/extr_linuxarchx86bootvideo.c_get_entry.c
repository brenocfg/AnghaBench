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
 unsigned int VIDEO_CURRENT_MODE ; 
 int getchar () ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  puts (char*) ; 

__attribute__((used)) static unsigned int get_entry(void)
{
	char entry_buf[4];
	int i, len = 0;
	int key;
	unsigned int v;

	do {
		key = getchar();

		if (key == '\b') {
			if (len > 0) {
				puts("\b \b");
				len--;
			}
		} else if ((key >= '0' && key <= '9') ||
			   (key >= 'A' && key <= 'Z') ||
			   (key >= 'a' && key <= 'z')) {
			if (len < sizeof entry_buf) {
				entry_buf[len++] = key;
				putchar(key);
			}
		}
	} while (key != '\r');
	putchar('\n');

	if (len == 0)
		return VIDEO_CURRENT_MODE; /* Default */

	v = 0;
	for (i = 0; i < len; i++) {
		v <<= 4;
		key = entry_buf[i] | 0x20;
		v += (key > '9') ? key-'a'+10 : key-'0';
	}

	return v;
}