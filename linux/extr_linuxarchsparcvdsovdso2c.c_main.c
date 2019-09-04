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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  go (void*,size_t,void*,size_t,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  map_input (char*,void**,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,size_t) ; 
 char* outfilename ; 
 int /*<<< orphan*/  printf (char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 

int main(int argc, char **argv)
{
	size_t raw_len, stripped_len;
	void *raw_addr, *stripped_addr;
	FILE *outfile;
	char *name, *tmp;
	int namelen;

	if (argc != 4) {
		printf("Usage: vdso2c RAW_INPUT STRIPPED_INPUT OUTPUT\n");
		return 1;
	}

	/*
	 * Figure out the struct name.  If we're writing to a .so file,
	 * generate raw output insted.
	 */
	name = strdup(argv[3]);
	namelen = strlen(name);
	if (namelen >= 3 && !strcmp(name + namelen - 3, ".so")) {
		name = NULL;
	} else {
		tmp = strrchr(name, '/');
		if (tmp)
			name = tmp + 1;
		tmp = strchr(name, '.');
		if (tmp)
			*tmp = '\0';
		for (tmp = name; *tmp; tmp++)
			if (*tmp == '-')
				*tmp = '_';
	}

	map_input(argv[1], &raw_addr, &raw_len, PROT_READ);
	map_input(argv[2], &stripped_addr, &stripped_len, PROT_READ);

	outfilename = argv[3];
	outfile = fopen(outfilename, "w");
	if (!outfile)
		err(1, "%s", argv[2]);

	go(raw_addr, raw_len, stripped_addr, stripped_len, outfile, name);

	munmap(raw_addr, raw_len);
	munmap(stripped_addr, stripped_len);
	fclose(outfile);

	return 0;
}