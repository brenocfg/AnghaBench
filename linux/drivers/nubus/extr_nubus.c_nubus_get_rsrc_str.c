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
struct nubus_dirent {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 unsigned char* nubus_dirptr (struct nubus_dirent const*) ; 
 unsigned char nubus_get_rom (unsigned char**,int,int /*<<< orphan*/ ) ; 

unsigned int nubus_get_rsrc_str(char *dest, const struct nubus_dirent *dirent,
				unsigned int len)
{
	char *t = dest;
	unsigned char *p = nubus_dirptr(dirent);

	while (len > 1) {
		unsigned char c = nubus_get_rom(&p, 1, dirent->mask);

		if (!c)
			break;
		*t++ = c;
		len--;
	}
	if (len > 0)
		*t = '\0';
	return t - dest;
}