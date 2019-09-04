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
typedef  int /*<<< orphan*/  u16 ;
struct x86_emulate_ctxt {TYPE_1__* ops; } ;
struct desc_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_segment ) (struct x86_emulate_ctxt*,int /*<<< orphan*/ *,struct desc_struct*,int /*<<< orphan*/ *,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct x86_emulate_ctxt*,int /*<<< orphan*/ *,struct desc_struct*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static u16 get_segment_selector(struct x86_emulate_ctxt *ctxt, unsigned seg)
{
	u16 selector;
	struct desc_struct desc;

	ctxt->ops->get_segment(ctxt, &selector, &desc, NULL, seg);
	return selector;
}