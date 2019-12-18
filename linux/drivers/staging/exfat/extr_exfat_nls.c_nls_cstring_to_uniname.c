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
typedef  char u8 ;
typedef  int u16 ;
struct uni_name_t {int* name; int name_len; int /*<<< orphan*/  name_hash; } ;
struct super_block {int dummy; } ;
struct nls_table {int dummy; } ;
struct TYPE_2__ {struct nls_table* nls_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_DEFAULT ; 
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int MAX_NAME_LENGTH ; 
 int /*<<< orphan*/  SET16_A (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UTF16_HOST_ENDIAN ; 
 int /*<<< orphan*/  bad_uni_chars ; 
 int /*<<< orphan*/  calc_checksum_2byte (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ convert_ch_to_uni (struct nls_table*,int*,char*,int*) ; 
 int /*<<< orphan*/  nls_upper (struct super_block*,int) ; 
 scalar_t__ nls_wstrchr (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int utf8s_to_utf16s (char*,int,int /*<<< orphan*/ ,int*,int) ; 

void nls_cstring_to_uniname(struct super_block *sb,
			    struct uni_name_t *p_uniname, u8 *p_cstring,
			    bool *p_lossy)
{
	int i, j;
	bool lossy = false;
	u8 *end_of_name;
	u8 upname[MAX_NAME_LENGTH * 2];
	u16 *uniname = p_uniname->name;
	struct nls_table *nls = EXFAT_SB(sb)->nls_io;

	/* strip all trailing spaces */
	end_of_name = p_cstring + strlen(p_cstring);

	while (*(--end_of_name) == ' ') {
		if (end_of_name < p_cstring)
			break;
	}
	*(++end_of_name) = '\0';

	if (strcmp(p_cstring, ".") && strcmp(p_cstring, "..")) {
		/* strip all trailing periods */
		while (*(--end_of_name) == '.') {
			if (end_of_name < p_cstring)
				break;
		}
		*(++end_of_name) = '\0';
	}

	if (*p_cstring == '\0')
		lossy = true;

	if (!nls) {
		i = utf8s_to_utf16s(p_cstring, MAX_NAME_LENGTH,
				    UTF16_HOST_ENDIAN, uniname,
				    MAX_NAME_LENGTH);
		for (j = 0; j < i; j++)
			SET16_A(upname + j * 2, nls_upper(sb, uniname[j]));
		uniname[i] = '\0';
	} else {
		i = 0;
		j = 0;
		while (j < (MAX_NAME_LENGTH - 1)) {
			if (*(p_cstring + i) == '\0')
				break;

			i += convert_ch_to_uni(nls, uniname,
					       (u8 *)(p_cstring + i), &lossy);

			if ((*uniname < 0x0020) ||
			    nls_wstrchr(bad_uni_chars, *uniname))
				lossy = true;

			SET16_A(upname + j * 2, nls_upper(sb, *uniname));

			uniname++;
			j++;
		}

		if (*(p_cstring + i) != '\0')
			lossy = true;
		*uniname = (u16)'\0';
	}

	p_uniname->name_len = j;
	p_uniname->name_hash = calc_checksum_2byte(upname, j << 1, 0,
						   CS_DEFAULT);

	if (p_lossy)
		*p_lossy = lossy;
}