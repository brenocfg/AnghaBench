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
struct dce_hwseq {int /*<<< orphan*/ * masks; int /*<<< orphan*/ * shifts; int /*<<< orphan*/ * regs; struct dc_context* ctx; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  hwseq_mask ; 
 int /*<<< orphan*/  hwseq_reg ; 
 int /*<<< orphan*/  hwseq_shift ; 
 struct dce_hwseq* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dce_hwseq *dce120_hwseq_create(
	struct dc_context *ctx)
{
	struct dce_hwseq *hws = kzalloc(sizeof(struct dce_hwseq), GFP_KERNEL);

	if (hws) {
		hws->ctx = ctx;
		hws->regs = &hwseq_reg;
		hws->shifts = &hwseq_shift;
		hws->masks = &hwseq_mask;
	}
	return hws;
}