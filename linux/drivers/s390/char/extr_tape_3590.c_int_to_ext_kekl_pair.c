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
struct tape390_kekl_pair {TYPE_1__* kekl; } ;
struct tape3592_kekl_pair {int count; int /*<<< orphan*/ * kekl; } ;
struct TYPE_2__ {void* type_on_tape; void* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 void* TAPE390_KEKL_TYPE_NONE ; 
 int /*<<< orphan*/  int_to_ext_kekl (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static void int_to_ext_kekl_pair(struct tape3592_kekl_pair *in,
				 struct tape390_kekl_pair *out)
{
	if (in->count == 0) {
		out->kekl[0].type = TAPE390_KEKL_TYPE_NONE;
		out->kekl[0].type_on_tape = TAPE390_KEKL_TYPE_NONE;
		out->kekl[1].type = TAPE390_KEKL_TYPE_NONE;
		out->kekl[1].type_on_tape = TAPE390_KEKL_TYPE_NONE;
	} else if (in->count == 1) {
		int_to_ext_kekl(&in->kekl[0], &out->kekl[0]);
		out->kekl[1].type = TAPE390_KEKL_TYPE_NONE;
		out->kekl[1].type_on_tape = TAPE390_KEKL_TYPE_NONE;
	} else if (in->count == 2) {
		int_to_ext_kekl(&in->kekl[0], &out->kekl[0]);
		int_to_ext_kekl(&in->kekl[1], &out->kekl[1]);
	} else {
		printk("Invalid KEKL number: %d\n", in->count);
		BUG();
	}
}