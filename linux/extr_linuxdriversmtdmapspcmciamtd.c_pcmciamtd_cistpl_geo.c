#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tuple_t ;
struct TYPE_6__ {int /*<<< orphan*/  bankwidth; } ;
struct pcmciamtd_dev {TYPE_1__ pcmcia_map; } ;
struct pcmcia_device {int dummy; } ;
struct TYPE_8__ {int ngeo; TYPE_2__* geo; } ;
typedef  TYPE_3__ cistpl_device_geo_t ;
struct TYPE_9__ {TYPE_3__ device_geo; } ;
typedef  TYPE_4__ cisparse_t ;
struct TYPE_7__ {int /*<<< orphan*/  interleave; int /*<<< orphan*/  partition; int /*<<< orphan*/  write_block; int /*<<< orphan*/  read_block; int /*<<< orphan*/  erase_block; int /*<<< orphan*/  buswidth; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ pcmcia_parse_tuple (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcmciamtd_cistpl_geo(struct pcmcia_device *p_dev,
				tuple_t *tuple,
				void *priv_data)
{
	struct pcmciamtd_dev *dev = priv_data;
	cisparse_t parse;
	cistpl_device_geo_t *t = &parse.device_geo;
	int i;

	if (pcmcia_parse_tuple(tuple, &parse))
		return -EINVAL;

	dev->pcmcia_map.bankwidth = t->geo[0].buswidth;
	/* from here on: DEBUG only */
	for (i = 0; i < t->ngeo; i++) {
		pr_debug("region: %d bankwidth = %u\n", i, t->geo[i].buswidth);
		pr_debug("region: %d erase_block = %u\n", i, t->geo[i].erase_block);
		pr_debug("region: %d read_block = %u\n", i, t->geo[i].read_block);
		pr_debug("region: %d write_block = %u\n", i, t->geo[i].write_block);
		pr_debug("region: %d partition = %u\n", i, t->geo[i].partition);
		pr_debug("region: %d interleave = %u\n", i, t->geo[i].interleave);
	}
	return 0;
}