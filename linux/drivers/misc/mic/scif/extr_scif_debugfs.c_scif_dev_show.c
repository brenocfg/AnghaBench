#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_5__ {char* node; } ;
struct TYPE_4__ {int maxid; int /*<<< orphan*/  nodeid; int /*<<< orphan*/  total; } ;

/* Variables and functions */
 scalar_t__ _scifdev_alive (TYPE_2__*) ; 
 TYPE_2__* scif_dev ; 
 TYPE_1__ scif_info ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,char*,...) ; 

__attribute__((used)) static int scif_dev_show(struct seq_file *s, void *unused)
{
	int node;

	seq_printf(s, "Total Nodes %d Self Node Id %d Maxid %d\n",
		   scif_info.total, scif_info.nodeid,
		   scif_info.maxid);

	if (!scif_dev)
		return 0;

	seq_printf(s, "%-16s\t%-16s\n", "node_id", "state");

	for (node = 0; node <= scif_info.maxid; node++)
		seq_printf(s, "%-16d\t%-16s\n", scif_dev[node].node,
			   _scifdev_alive(&scif_dev[node]) ?
			   "Running" : "Offline");
	return 0;
}