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
typedef  int u64 ;
struct flag_table {int flag; char* str; } ;
typedef  int /*<<< orphan*/  extra ;

/* Variables and functions */
 int append_str (char*,char**,int*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static char *flag_string(char *buf, int buf_len, u64 flags,
			 struct flag_table *table, int table_size)
{
	char extra[32];
	char *p = buf;
	int len = buf_len;
	int no_room = 0;
	int i;

	/* make sure there is at least 2 so we can form "*" */
	if (len < 2)
		return "";

	len--;	/* leave room for a nul */
	for (i = 0; i < table_size; i++) {
		if (flags & table[i].flag) {
			no_room = append_str(buf, &p, &len, table[i].str);
			if (no_room)
				break;
			flags &= ~table[i].flag;
		}
	}

	/* any undocumented bits left? */
	if (!no_room && flags) {
		snprintf(extra, sizeof(extra), "bits 0x%llx", flags);
		no_room = append_str(buf, &p, &len, extra);
	}

	/* add * if ran out of room */
	if (no_room) {
		/* may need to back up to add space for a '*' */
		if (len == 0)
			--p;
		*p++ = '*';
	}

	/* add final nul - space already allocated above */
	*p = 0;
	return buf;
}