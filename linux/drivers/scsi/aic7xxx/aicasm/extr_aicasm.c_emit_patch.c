#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  end_addr; int /*<<< orphan*/  begin_addr; scalar_t__ func_num; TYPE_3__* patches; } ;
typedef  TYPE_1__ scope_t ;
struct TYPE_8__ {scalar_t__ skip_instr; int /*<<< orphan*/  skip_patch; int /*<<< orphan*/  begin; scalar_t__ patch_func; } ;
typedef  TYPE_2__ patch_t ;
struct TYPE_9__ {scalar_t__ skip_instr; int /*<<< orphan*/  skip_patch; } ;
typedef  TYPE_3__ patch_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  patches ; 
 int /*<<< orphan*/  stop (char*,int /*<<< orphan*/ ) ; 

void
emit_patch(scope_t *scope, int patch)
{
	patch_info_t *pinfo;
	patch_t *new_patch;

	pinfo = &scope->patches[patch];

	if (pinfo->skip_instr == 0)
		/* No-Op patch */
		return;

	new_patch = (patch_t *)malloc(sizeof(*new_patch));

	if (new_patch == NULL)
		stop("Could not malloc patch structure", EX_OSERR);

	memset(new_patch, 0, sizeof(*new_patch));

	if (patch == 0) {
		new_patch->patch_func = scope->func_num;
		new_patch->begin = scope->begin_addr;
	} else {
		new_patch->patch_func = 0;
		new_patch->begin = scope->end_addr;
	}
	new_patch->skip_instr = pinfo->skip_instr;
	new_patch->skip_patch = pinfo->skip_patch;
	STAILQ_INSERT_TAIL(&patches, new_patch, links);
}