#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int lfb_base; int lfb_linelength; int lfb_height; int lfb_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_MEMORY_WC ; 
 int /*<<< orphan*/  efifb_setup_from_dmi (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mem_flags ; 
 TYPE_1__ screen_info ; 
 int simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strsep (char**,char*) ; 
 int use_bgrt ; 

__attribute__((used)) static int efifb_setup(char *options)
{
	char *this_opt;

	if (options && *options) {
		while ((this_opt = strsep(&options, ",")) != NULL) {
			if (!*this_opt) continue;

			efifb_setup_from_dmi(&screen_info, this_opt);

			if (!strncmp(this_opt, "base:", 5))
				screen_info.lfb_base = simple_strtoul(this_opt+5, NULL, 0);
			else if (!strncmp(this_opt, "stride:", 7))
				screen_info.lfb_linelength = simple_strtoul(this_opt+7, NULL, 0) * 4;
			else if (!strncmp(this_opt, "height:", 7))
				screen_info.lfb_height = simple_strtoul(this_opt+7, NULL, 0);
			else if (!strncmp(this_opt, "width:", 6))
				screen_info.lfb_width = simple_strtoul(this_opt+6, NULL, 0);
			else if (!strcmp(this_opt, "nowc"))
				mem_flags &= ~EFI_MEMORY_WC;
			else if (!strcmp(this_opt, "nobgrt"))
				use_bgrt = false;
		}
	}

	return 0;
}