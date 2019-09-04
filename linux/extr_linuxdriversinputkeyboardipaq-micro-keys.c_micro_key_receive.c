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
struct ipaq_micro_keys {int /*<<< orphan*/  input; int /*<<< orphan*/ * codes; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  micro_keycodes ; 

__attribute__((used)) static void micro_key_receive(void *data, int len, unsigned char *msg)
{
	struct ipaq_micro_keys *keys = data;
	int key, down;

	down = 0x80 & msg[0];
	key  = 0x7f & msg[0];

	if (key < ARRAY_SIZE(micro_keycodes)) {
		input_report_key(keys->input, keys->codes[key], down);
		input_sync(keys->input);
	}
}