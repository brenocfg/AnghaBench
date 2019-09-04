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
struct parser_exec_state {TYPE_1__* info; struct intel_vgpu* vgpu; } ;
struct intel_vgpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBADRQC ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int unexpected_cmd(struct parser_exec_state *s)
{
	struct intel_vgpu *vgpu = s->vgpu;

	gvt_vgpu_err("Unexpected %s in command buffer!\n", s->info->name);

	return -EBADRQC;
}