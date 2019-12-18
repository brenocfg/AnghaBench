#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct uni_name_t {scalar_t__* name; } ;
struct super_block {int dummy; } ;
struct nls_table {int dummy; } ;
struct dos_name_t {int* name; int name_case; } ;
struct TYPE_2__ {struct nls_table* nls_disk; } ;

/* Variables and functions */
 int DOS_NAME_LENGTH ; 
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int MAX_NAME_LENGTH ; 
 scalar_t__ convert_ch_to_uni (struct nls_table*,scalar_t__*,int*,int /*<<< orphan*/ *) ; 

void nls_dosname_to_uniname(struct super_block *sb,
			    struct uni_name_t *p_uniname,
			    struct dos_name_t *p_dosname)
{
	int i = 0, j, n = 0;
	u8 buf[DOS_NAME_LENGTH + 2];
	u8 *dosname = p_dosname->name;
	u16 *uniname = p_uniname->name;
	struct nls_table *nls = EXFAT_SB(sb)->nls_disk;

	if (*dosname == 0x05) {
		*buf = 0xE5;
		i++;
		n++;
	}

	for (; i < 8; i++, n++) {
		if (*(dosname + i) == ' ')
			break;

		if ((*(dosname + i) >= 'A') && (*(dosname + i) <= 'Z') &&
		    (p_dosname->name_case & 0x08))
			*(buf + n) = *(dosname + i) + ('a' - 'A');
		else
			*(buf + n) = *(dosname + i);
	}
	if (*(dosname + 8) != ' ') {
		*(buf + n) = '.';
		n++;
	}

	for (i = 8; i < DOS_NAME_LENGTH; i++, n++) {
		if (*(dosname + i) == ' ')
			break;

		if ((*(dosname + i) >= 'A') && (*(dosname + i) <= 'Z') &&
		    (p_dosname->name_case & 0x10))
			*(buf + n) = *(dosname + i) + ('a' - 'A');
		else
			*(buf + n) = *(dosname + i);
	}
	*(buf + n) = '\0';

	i = 0;
	j = 0;
	while (j < (MAX_NAME_LENGTH - 1)) {
		if (*(buf + i) == '\0')
			break;

		i += convert_ch_to_uni(nls, uniname, (buf + i), NULL);

		uniname++;
		j++;
	}

	*uniname = (u16)'\0';
}