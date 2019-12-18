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
 int MAX_SETUP_ARGS ; 
 int SETUP_BUFFER_SIZE ; 
 int done_setup ; 
 char** setup_args ; 
 char* setup_buffer ; 
 scalar_t__* setup_used ; 
 char* strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,scalar_t__) ; 

__attribute__((used)) static int
wd33c93_setup(char *str)
{
	int i;
	char *p1, *p2;

	/* The kernel does some processing of the command-line before calling
	 * this function: If it begins with any decimal or hex number arguments,
	 * ints[0] = how many numbers found and ints[1] through [n] are the values
	 * themselves. str points to where the non-numeric arguments (if any)
	 * start: We do our own parsing of those. We construct synthetic 'nosync'
	 * keywords out of numeric args (to maintain compatibility with older
	 * versions) and then add the rest of the arguments.
	 */

	p1 = setup_buffer;
	*p1 = '\0';
	if (str)
		strncpy(p1, str, SETUP_BUFFER_SIZE - strlen(setup_buffer));
	setup_buffer[SETUP_BUFFER_SIZE - 1] = '\0';
	p1 = setup_buffer;
	i = 0;
	while (*p1 && (i < MAX_SETUP_ARGS)) {
		p2 = strchr(p1, ',');
		if (p2) {
			*p2 = '\0';
			if (p1 != p2)
				setup_args[i] = p1;
			p1 = p2 + 1;
			i++;
		} else {
			setup_args[i] = p1;
			break;
		}
	}
	for (i = 0; i < MAX_SETUP_ARGS; i++)
		setup_used[i] = 0;
	done_setup = 1;

	return 1;
}