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
 int ENOMEM ; 
 scalar_t__ isspace (char) ; 
 char** realloc_argv (unsigned int*,char**) ; 
 char* skip_spaces (char*) ; 

int dm_split_args(int *argc, char ***argvp, char *input)
{
	char *start, *end = input, *out, **argv = NULL;
	unsigned array_size = 0;

	*argc = 0;

	if (!input) {
		*argvp = NULL;
		return 0;
	}

	argv = realloc_argv(&array_size, argv);
	if (!argv)
		return -ENOMEM;

	while (1) {
		/* Skip whitespace */
		start = skip_spaces(end);

		if (!*start)
			break;	/* success, we hit the end */

		/* 'out' is used to remove any back-quotes */
		end = out = start;
		while (*end) {
			/* Everything apart from '\0' can be quoted */
			if (*end == '\\' && *(end + 1)) {
				*out++ = *(end + 1);
				end += 2;
				continue;
			}

			if (isspace(*end))
				break;	/* end of token */

			*out++ = *end++;
		}

		/* have we already filled the array ? */
		if ((*argc + 1) > array_size) {
			argv = realloc_argv(&array_size, argv);
			if (!argv)
				return -ENOMEM;
		}

		/* we know this is whitespace */
		if (*end)
			end++;

		/* terminate the string and put it in the array */
		*out = '\0';
		argv[*argc] = start;
		(*argc)++;
	}

	*argvp = argv;
	return 0;
}