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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct imon_panel_key_table {int hw_code; int /*<<< orphan*/  keycode; } ;
struct imon_context {int release_code; TYPE_1__* dev_descr; } ;
struct TYPE_2__ {struct imon_panel_key_table* key_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_RESERVED ; 

__attribute__((used)) static u32 imon_panel_key_lookup(struct imon_context *ictx, u64 code)
{
	int i;
	u32 keycode = KEY_RESERVED;
	struct imon_panel_key_table *key_table = ictx->dev_descr->key_table;

	for (i = 0; key_table[i].hw_code != 0; i++) {
		if (key_table[i].hw_code == (code | 0xffee)) {
			keycode = key_table[i].keycode;
			break;
		}
	}
	ictx->release_code = false;
	return keycode;
}