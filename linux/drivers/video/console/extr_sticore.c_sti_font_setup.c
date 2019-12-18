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
 int MAX_STI_ROMS ; 
 void** font_height ; 
 void** font_index ; 
 char** font_name ; 
 void** font_width ; 
 void* simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int sti_font_setup(char *str)
{
	char *x;
	int i = 0;

	/* we accept sti_font=VGA8x16, sti_font=10x20, sti_font=10*20 
	 * or sti_font=7 style command lines. */

	while (i<MAX_STI_ROMS && str && *str) {
		if (*str>='0' && *str<='9') {
			if ((x = strchr(str, 'x')) || (x = strchr(str, '*'))) {
				font_height[i] = simple_strtoul(str, NULL, 0);
				font_width[i] = simple_strtoul(x+1, NULL, 0);
			} else {
				font_index[i] = simple_strtoul(str, NULL, 0);
			}
		} else {
			font_name[i] = str;	/* fb font name */
		}

		if ((x = strchr(str, ',')))
			*x++ = 0;
		str = x;

		i++;
	}

	return 1;
}