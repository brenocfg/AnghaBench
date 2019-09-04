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
struct ssif_info {int /*<<< orphan*/  addr_info; TYPE_1__* client; int /*<<< orphan*/  addr_source; } ;
struct ipmi_smi_info {int /*<<< orphan*/ * dev; int /*<<< orphan*/  addr_info; int /*<<< orphan*/  addr_src; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_smi_info(void *send_info, struct ipmi_smi_info *data)
{
	struct ssif_info *ssif_info = send_info;

	data->addr_src = ssif_info->addr_source;
	data->dev = &ssif_info->client->dev;
	data->addr_info = ssif_info->addr_info;
	get_device(data->dev);

	return 0;
}