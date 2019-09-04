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
struct its_collection {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_id; struct its_collection* col; struct its_device* dev; } ;
struct its_cmd_desc {TYPE_1__ its_movi_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  its_build_movi_cmd ; 
 int /*<<< orphan*/  its_send_single_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct its_cmd_desc*) ; 

__attribute__((used)) static void its_send_movi(struct its_device *dev,
			  struct its_collection *col, u32 id)
{
	struct its_cmd_desc desc;

	desc.its_movi_cmd.dev = dev;
	desc.its_movi_cmd.col = col;
	desc.its_movi_cmd.event_id = id;

	its_send_single_command(dev->its, its_build_movi_cmd, &desc);
}