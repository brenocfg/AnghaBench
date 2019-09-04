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
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  addr_info; int /*<<< orphan*/  addr_source; } ;
struct smi_info {TYPE_1__ io; } ;
struct ipmi_smi_info {int /*<<< orphan*/  addr_info; int /*<<< orphan*/  dev; int /*<<< orphan*/  addr_src; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_smi_info(void *send_info, struct ipmi_smi_info *data)
{
	struct smi_info *smi = send_info;

	data->addr_src = smi->io.addr_source;
	data->dev = smi->io.dev;
	data->addr_info = smi->io.addr_info;
	get_device(smi->io.dev);

	return 0;
}