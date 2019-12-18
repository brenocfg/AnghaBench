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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  kfree (char**) ; 
 char** kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char**,char**,unsigned int) ; 

__attribute__((used)) static char **realloc_argv(unsigned *size, char **old_argv)
{
	char **argv;
	unsigned new_size;
	gfp_t gfp;

	if (*size) {
		new_size = *size * 2;
		gfp = GFP_KERNEL;
	} else {
		new_size = 8;
		gfp = GFP_NOIO;
	}
	argv = kmalloc_array(new_size, sizeof(*argv), gfp);
	if (argv && old_argv) {
		memcpy(argv, old_argv, *size * sizeof(*argv));
		*size = new_size;
	}

	kfree(old_argv);
	return argv;
}