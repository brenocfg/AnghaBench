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
struct integrated_info {int dummy; } ;
struct dc_bios {int dummy; } ;
struct bios_parser {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int /*<<< orphan*/ ) ; 
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 scalar_t__ BP_RESULT_OK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ construct_integrated_info (struct bios_parser*,struct integrated_info*) ; 
 int /*<<< orphan*/  kfree (struct integrated_info*) ; 
 struct integrated_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct integrated_info *bios_parser_create_integrated_info(
	struct dc_bios *dcb)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);
	struct integrated_info *info = NULL;

	info = kzalloc(sizeof(struct integrated_info), GFP_KERNEL);

	if (info == NULL) {
		ASSERT_CRITICAL(0);
		return NULL;
	}

	if (construct_integrated_info(bp, info) == BP_RESULT_OK)
		return info;

	kfree(info);

	return NULL;
}