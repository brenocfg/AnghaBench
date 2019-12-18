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
typedef  scalar_t__ u8 ;
struct twl4030_ins {int /*<<< orphan*/  delay; int /*<<< orphan*/  pmb_message; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ END_OF_SCRIPT ; 
 int twl4030_write_script_ins (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int twl4030_write_script(u8 address, struct twl4030_ins *script,
				       int len)
{
	int err = -EINVAL;

	for (; len; len--, address++, script++) {
		if (len == 1) {
			err = twl4030_write_script_ins(address,
						script->pmb_message,
						script->delay,
						END_OF_SCRIPT);
			if (err)
				break;
		} else {
			err = twl4030_write_script_ins(address,
						script->pmb_message,
						script->delay,
						address + 1);
			if (err)
				break;
		}
	}
	return err;
}