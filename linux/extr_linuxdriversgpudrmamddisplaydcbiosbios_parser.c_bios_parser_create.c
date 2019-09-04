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
struct bios_parser {struct dc_bios base; } ;
typedef  enum dce_version { ____Placeholder_dce_version } dce_version ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ bios_parser_construct (struct bios_parser*,struct bp_init_data*,int) ; 
 int /*<<< orphan*/  kfree (struct bios_parser*) ; 
 struct bios_parser* kzalloc (int,int /*<<< orphan*/ ) ; 

struct dc_bios *bios_parser_create(
	struct bp_init_data *init,
	enum dce_version dce_version)
{
	struct bios_parser *bp = NULL;

	bp = kzalloc(sizeof(struct bios_parser), GFP_KERNEL);
	if (!bp)
		return NULL;

	if (bios_parser_construct(bp, init, dce_version))
		return &bp->base;

	kfree(bp);
	BREAK_TO_DEBUGGER();
	return NULL;
}