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
typedef  scalar_t__ u16 ;
struct uni_name_t {scalar_t__* name; } ;
struct super_block {int dummy; } ;
struct nls_table {int dummy; } ;
struct TYPE_2__ {struct nls_table* nls_io; } ;

/* Variables and functions */
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int MAX_CHARSET_SIZE ; 
 int MAX_NAME_LENGTH ; 
 int /*<<< orphan*/  UTF16_HOST_ENDIAN ; 
 int convert_uni_to_ch (struct nls_table*,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int utf16s_to_utf8s (scalar_t__*,int,int /*<<< orphan*/ ,char*,int) ; 

void nls_uniname_to_cstring(struct super_block *sb, u8 *p_cstring,
			    struct uni_name_t *p_uniname)
{
	int i, j, len;
	u8 buf[MAX_CHARSET_SIZE];
	u16 *uniname = p_uniname->name;
	struct nls_table *nls = EXFAT_SB(sb)->nls_io;

	if (!nls) {
		len = utf16s_to_utf8s(uniname, MAX_NAME_LENGTH,
				      UTF16_HOST_ENDIAN, p_cstring,
				      MAX_NAME_LENGTH);
		p_cstring[len] = 0;
		return;
	}

	i = 0;
	while (i < (MAX_NAME_LENGTH - 1)) {
		if (*uniname == (u16)'\0')
			break;

		len = convert_uni_to_ch(nls, buf, *uniname, NULL);

		if (len > 1) {
			for (j = 0; j < len; j++)
				*p_cstring++ = (char)*(buf + j);
		} else { /* len == 1 */
			*p_cstring++ = (char)*buf;
		}

		uniname++;
		i++;
	}

	*p_cstring = '\0';
}