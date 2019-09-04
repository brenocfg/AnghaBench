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
struct mtd_partition {unsigned long long size; unsigned long long offset; unsigned int mask_flags; unsigned char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct mtd_partition* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mtd_partition*) ; 
 unsigned int MTD_POWERUP_LOCK ; 
 unsigned int MTD_WRITEABLE ; 
 unsigned long long OFFSET_CONTINUOUS ; 
 unsigned long long SIZE_REMAINING ; 
 int /*<<< orphan*/  dbg (char*) ; 
 struct mtd_partition* kzalloc (int,int /*<<< orphan*/ ) ; 
 unsigned long long memparse (char*,char**) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  sprintf (unsigned char*,char*,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (unsigned char*,char*,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static struct mtd_partition * newpart(char *s,
				      char **retptr,
				      int *num_parts,
				      int this_part,
				      unsigned char **extra_mem_ptr,
				      int extra_mem_size)
{
	struct mtd_partition *parts;
	unsigned long long size, offset = OFFSET_CONTINUOUS;
	char *name;
	int name_len;
	unsigned char *extra_mem;
	char delim;
	unsigned int mask_flags;

	/* fetch the partition size */
	if (*s == '-') {
		/* assign all remaining space to this partition */
		size = SIZE_REMAINING;
		s++;
	} else {
		size = memparse(s, &s);
		if (!size) {
			pr_err("partition has size 0\n");
			return ERR_PTR(-EINVAL);
		}
	}

	/* fetch partition name and flags */
	mask_flags = 0; /* this is going to be a regular partition */
	delim = 0;

	/* check for offset */
	if (*s == '@') {
		s++;
		offset = memparse(s, &s);
	}

	/* now look for name */
	if (*s == '(')
		delim = ')';

	if (delim) {
		char *p;

		name = ++s;
		p = strchr(name, delim);
		if (!p) {
			pr_err("no closing %c found in partition name\n", delim);
			return ERR_PTR(-EINVAL);
		}
		name_len = p - name;
		s = p + 1;
	} else {
		name = NULL;
		name_len = 13; /* Partition_000 */
	}

	/* record name length for memory allocation later */
	extra_mem_size += name_len + 1;

	/* test for options */
	if (strncmp(s, "ro", 2) == 0) {
		mask_flags |= MTD_WRITEABLE;
		s += 2;
	}

	/* if lk is found do NOT unlock the MTD partition*/
	if (strncmp(s, "lk", 2) == 0) {
		mask_flags |= MTD_POWERUP_LOCK;
		s += 2;
	}

	/* test if more partitions are following */
	if (*s == ',') {
		if (size == SIZE_REMAINING) {
			pr_err("no partitions allowed after a fill-up partition\n");
			return ERR_PTR(-EINVAL);
		}
		/* more partitions follow, parse them */
		parts = newpart(s + 1, &s, num_parts, this_part + 1,
				&extra_mem, extra_mem_size);
		if (IS_ERR(parts))
			return parts;
	} else {
		/* this is the last partition: allocate space for all */
		int alloc_size;

		*num_parts = this_part + 1;
		alloc_size = *num_parts * sizeof(struct mtd_partition) +
			     extra_mem_size;

		parts = kzalloc(alloc_size, GFP_KERNEL);
		if (!parts)
			return ERR_PTR(-ENOMEM);
		extra_mem = (unsigned char *)(parts + *num_parts);
	}

	/*
	 * enter this partition (offset will be calculated later if it is
	 * OFFSET_CONTINUOUS at this point)
	 */
	parts[this_part].size = size;
	parts[this_part].offset = offset;
	parts[this_part].mask_flags = mask_flags;
	if (name)
		strlcpy(extra_mem, name, name_len + 1);
	else
		sprintf(extra_mem, "Partition_%03d", this_part);
	parts[this_part].name = extra_mem;
	extra_mem += name_len + 1;

	dbg(("partition %d: name <%s>, offset %llx, size %llx, mask flags %x\n",
	     this_part, parts[this_part].name, parts[this_part].offset,
	     parts[this_part].size, parts[this_part].mask_flags));

	/* return (updated) pointer to extra_mem memory */
	if (extra_mem_ptr)
		*extra_mem_ptr = extra_mem;

	/* return (updated) pointer command line string */
	*retptr = s;

	/* return partition table */
	return parts;
}