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
typedef  char u8 ;
typedef  int /*<<< orphan*/  str_count ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int strlen (char*) ; 

void fat_attach_count_to_dos_name(u8 *dosname, s32 count)
{
	int i, j, length;
	char str_count[6];

	snprintf(str_count, sizeof(str_count), "~%d", count);
	length = strlen(str_count);

	i = 0;
	j = 0;
	while (j <= (8 - length)) {
		i = j;
		if (dosname[j] == ' ')
			break;
		if (dosname[j] & 0x80)
			j += 2;
		else
			j++;
	}

	for (j = 0; j < length; i++, j++)
		dosname[i] = (u8)str_count[j];

	if (i == 7)
		dosname[7] = ' ';
}