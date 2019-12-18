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
typedef  int /*<<< orphan*/  u32 ;
struct its_device {int /*<<< orphan*/  its; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_id; struct its_device* dev; } ;
struct its_cmd_desc {TYPE_1__ its_int_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  its_build_int_cmd ; 
 int /*<<< orphan*/  its_send_single_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct its_cmd_desc*) ; 

__attribute__((used)) static void its_send_int(struct its_device *dev, u32 event_id)
{
	struct its_cmd_desc desc;

	desc.its_int_cmd.dev = dev;
	desc.its_int_cmd.event_id = event_id;

	its_send_single_command(dev->its, its_build_int_cmd, &desc);
}