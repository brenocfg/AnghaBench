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
struct gds_subvector {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBC_TOLOWER (unsigned char*,int) ; 
 int /*<<< orphan*/  sclp_ebcasc_str (unsigned char*,int) ; 
 int sclp_switch_cases (unsigned char*,int) ; 
 int /*<<< orphan*/  sclp_tty_input (unsigned char*,int) ; 
 scalar_t__ sclp_tty_tolower ; 

__attribute__((used)) static void sclp_get_input(struct gds_subvector *sv)
{
	unsigned char *str;
	int count;

	str = (unsigned char *) (sv + 1);
	count = sv->length - sizeof(*sv);
	if (sclp_tty_tolower)
		EBC_TOLOWER(str, count);
	count = sclp_switch_cases(str, count);
	/* convert EBCDIC to ASCII (modify original input in SCCB) */
	sclp_ebcasc_str(str, count);

	/* transfer input to high level driver */
	sclp_tty_input(str, count);
}