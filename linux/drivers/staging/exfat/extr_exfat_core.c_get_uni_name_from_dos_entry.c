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
typedef  int u8 ;
struct uni_name_t {int dummy; } ;
struct super_block {int dummy; } ;
struct dos_name_t {int name_case; int /*<<< orphan*/  name; } ;
struct dos_dentry_t {int lcase; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOS_NAME_LENGTH ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nls_dosname_to_uniname (struct super_block*,struct uni_name_t*,struct dos_name_t*) ; 

void get_uni_name_from_dos_entry(struct super_block *sb,
				 struct dos_dentry_t *ep,
				 struct uni_name_t *p_uniname, u8 mode)
{
	struct dos_name_t dos_name;

	if (mode == 0x0)
		dos_name.name_case = 0x0;
	else
		dos_name.name_case = ep->lcase;

	memcpy(dos_name.name, ep->name, DOS_NAME_LENGTH);
	nls_dosname_to_uniname(sb, p_uniname, &dos_name);
}