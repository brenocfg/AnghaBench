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
struct TYPE_2__ {int /*<<< orphan*/  s32; int /*<<< orphan*/  s16; int /*<<< orphan*/  s8; } ;
struct hid_item {int size; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */

__attribute__((used)) static s32 item_sdata(struct hid_item *item)
{
	switch (item->size) {
	case 1: return item->data.s8;
	case 2: return item->data.s16;
	case 4: return item->data.s32;
	}
	return 0;
}