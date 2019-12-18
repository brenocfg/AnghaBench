#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct its_vlpi_map {int /*<<< orphan*/  db_enabled; int /*<<< orphan*/  vintid; int /*<<< orphan*/  vpe; } ;
struct TYPE_3__ {struct its_vlpi_map* vlpi_maps; } ;
struct its_device {int /*<<< orphan*/  its; TYPE_1__ event_map; } ;
struct TYPE_4__ {size_t event_id; int /*<<< orphan*/  db_enabled; int /*<<< orphan*/  virt_id; struct its_device* dev; int /*<<< orphan*/  vpe; } ;
struct its_cmd_desc {TYPE_2__ its_vmapti_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  its_build_vmapti_cmd ; 
 int /*<<< orphan*/  its_send_single_vcommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct its_cmd_desc*) ; 

__attribute__((used)) static void its_send_vmapti(struct its_device *dev, u32 id)
{
	struct its_vlpi_map *map = &dev->event_map.vlpi_maps[id];
	struct its_cmd_desc desc;

	desc.its_vmapti_cmd.vpe = map->vpe;
	desc.its_vmapti_cmd.dev = dev;
	desc.its_vmapti_cmd.virt_id = map->vintid;
	desc.its_vmapti_cmd.event_id = id;
	desc.its_vmapti_cmd.db_enabled = map->db_enabled;

	its_send_single_vcommand(dev->its, its_build_vmapti_cmd, &desc);
}