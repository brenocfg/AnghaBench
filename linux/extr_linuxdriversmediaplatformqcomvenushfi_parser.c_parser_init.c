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
typedef  int /*<<< orphan*/  u32 ;
struct venus_inst {int /*<<< orphan*/  session_type; int /*<<< orphan*/  hfi_codec; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_V1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parser_init(struct venus_inst *inst, u32 *codecs, u32 *domain)
{
	if (!inst || !IS_V1(inst->core))
		return;

	*codecs = inst->hfi_codec;
	*domain = inst->session_type;
}