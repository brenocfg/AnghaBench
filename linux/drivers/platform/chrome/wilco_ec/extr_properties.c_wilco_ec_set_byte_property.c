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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wilco_ec_property_msg {int length; int /*<<< orphan*/ * data; int /*<<< orphan*/  property_id; } ;
struct wilco_ec_device {int dummy; } ;

/* Variables and functions */
 int wilco_ec_set_property (struct wilco_ec_device*,struct wilco_ec_property_msg*) ; 

int wilco_ec_set_byte_property(struct wilco_ec_device *ec, u32 property_id,
			       u8 val)
{
	struct wilco_ec_property_msg msg;

	msg.property_id = property_id;
	msg.data[0] = val;
	msg.length = 1;

	return wilco_ec_set_property(ec, &msg);
}