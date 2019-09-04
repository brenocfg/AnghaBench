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
typedef  scalar_t__ u32 ;
struct venus_inst {scalar_t__ session_type; TYPE_1__* core; } ;
struct venus_caps {scalar_t__ codec; scalar_t__ domain; int valid; } ;
struct TYPE_2__ {struct venus_caps* caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_V1 (TYPE_1__*) ; 
 unsigned int MAX_CODEC_NUM ; 

__attribute__((used)) static void parser_fini(struct venus_inst *inst, u32 codecs, u32 domain)
{
	struct venus_caps *caps, *cap;
	unsigned int i;
	u32 dom;

	if (!inst || !IS_V1(inst->core))
		return;

	caps = inst->core->caps;
	dom = inst->session_type;

	for (i = 0; i < MAX_CODEC_NUM; i++) {
		cap = &caps[i];
		if (cap->codec & codecs && cap->domain == dom)
			cap->valid = true;
	}
}