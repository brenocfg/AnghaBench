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
typedef  size_t u32 ;
struct tid_rb_node {size_t rcventry; } ;
struct hfi1_filedata {int /*<<< orphan*/ ** entry_to_rb; TYPE_1__* uctxt; } ;
struct TYPE_2__ {size_t expected_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_tid_node (struct hfi1_filedata*,struct tid_rb_node*) ; 

__attribute__((used)) static void cacheless_tid_rb_remove(struct hfi1_filedata *fdata,
				    struct tid_rb_node *tnode)
{
	u32 base = fdata->uctxt->expected_base;

	fdata->entry_to_rb[tnode->rcventry - base] = NULL;
	clear_tid_node(fdata, tnode);
}