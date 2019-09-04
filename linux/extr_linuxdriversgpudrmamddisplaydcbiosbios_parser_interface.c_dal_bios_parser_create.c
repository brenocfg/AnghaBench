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
struct dc_bios {int dummy; } ;
struct bp_init_data {int dummy; } ;
typedef  enum dce_version { ____Placeholder_dce_version } dce_version ;

/* Variables and functions */
 struct dc_bios* bios_parser_create (struct bp_init_data*,int) ; 
 struct dc_bios* firmware_parser_create (struct bp_init_data*,int) ; 

struct dc_bios *dal_bios_parser_create(
	struct bp_init_data *init,
	enum dce_version dce_version)
{
	struct dc_bios *bios = NULL;

	bios = firmware_parser_create(init, dce_version);

	/* Fall back to old bios parser for older asics */
	if (bios == NULL)
		bios = bios_parser_create(init, dce_version);

	return bios;
}