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
struct ddb_regmap {int dummy; } ;
struct ddb_port {size_t nr; size_t lnr; size_t pnr; int gap; scalar_t__ class; scalar_t__ type; char* name; int /*<<< orphan*/  i2c; TYPE_1__* dvb; int /*<<< orphan*/  i2c_gate_lock; int /*<<< orphan*/  obr; struct ddb* dev; } ;
struct ddb_info {size_t port_num; scalar_t__ type; struct ddb_regmap* regmap; } ;
struct ddb {size_t port_num; TYPE_2__* link; int /*<<< orphan*/  dev; struct ddb_port* port; int /*<<< orphan*/ * adap; } ;
struct TYPE_4__ {struct ddb_info* info; } ;
struct TYPE_3__ {int /*<<< orphan*/ * adap; } ;

/* Variables and functions */
 scalar_t__ DDB_CI_EXTERNAL_XO2 ; 
 scalar_t__ DDB_CI_EXTERNAL_XO2_B ; 
 size_t DDB_MAX_LINK ; 
#define  DDB_OCTOPUS 132 
#define  DDB_OCTOPUS_CI 131 
#define  DDB_OCTOPUS_MAX 130 
#define  DDB_OCTOPUS_MAX_CT 129 
#define  DDB_OCTOPUS_MCI 128 
 scalar_t__ DDB_PORT_CI ; 
 scalar_t__ DDB_PORT_NONE ; 
 int /*<<< orphan*/  ci_bitrate ; 
 int /*<<< orphan*/  ddb_input_init (struct ddb_port*,int,int,int) ; 
 int /*<<< orphan*/  ddb_output_init (struct ddb_port*,size_t) ; 
 int /*<<< orphan*/  ddb_port_match_i2c (struct ddb_port*) ; 
 int /*<<< orphan*/  ddb_port_match_link_i2c (struct ddb_port*) ; 
 int /*<<< orphan*/  ddb_port_probe (struct ddb_port*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,size_t,size_t,size_t,size_t,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void ddb_ports_init(struct ddb *dev)
{
	u32 i, l, p;
	struct ddb_port *port;
	const struct ddb_info *info;
	const struct ddb_regmap *rm;

	for (p = l = 0; l < DDB_MAX_LINK; l++) {
		info = dev->link[l].info;
		if (!info)
			continue;
		rm = info->regmap;
		if (!rm)
			continue;
		for (i = 0; i < info->port_num; i++, p++) {
			port = &dev->port[p];
			port->dev = dev;
			port->nr = i;
			port->lnr = l;
			port->pnr = p;
			port->gap = 0xffffffff;
			port->obr = ci_bitrate;
			mutex_init(&port->i2c_gate_lock);

			if (!ddb_port_match_i2c(port)) {
				if (info->type == DDB_OCTOPUS_MAX)
					ddb_port_match_link_i2c(port);
			}

			ddb_port_probe(port);

			port->dvb[0].adap = &dev->adap[2 * p];
			port->dvb[1].adap = &dev->adap[2 * p + 1];

			if (port->class == DDB_PORT_NONE && i && p &&
			    dev->port[p - 1].type == DDB_CI_EXTERNAL_XO2) {
				port->class = DDB_PORT_CI;
				port->type = DDB_CI_EXTERNAL_XO2_B;
				port->name = "DuoFlex CI_B";
				port->i2c = dev->port[p - 1].i2c;
			}

			dev_info(dev->dev, "Port %u: Link %u, Link Port %u (TAB %u): %s\n",
				 port->pnr, port->lnr, port->nr, port->nr + 1,
				 port->name);

			if (port->class == DDB_PORT_CI &&
			    port->type == DDB_CI_EXTERNAL_XO2) {
				ddb_input_init(port, 2 * i, 0, 2 * i);
				ddb_output_init(port, i);
				continue;
			}

			if (port->class == DDB_PORT_CI &&
			    port->type == DDB_CI_EXTERNAL_XO2_B) {
				ddb_input_init(port, 2 * i - 1, 0, 2 * i - 1);
				ddb_output_init(port, i);
				continue;
			}

			if (port->class == DDB_PORT_NONE)
				continue;

			switch (dev->link[l].info->type) {
			case DDB_OCTOPUS_CI:
				if (i >= 2) {
					ddb_input_init(port, 2 + i, 0, 2 + i);
					ddb_input_init(port, 4 + i, 1, 4 + i);
					ddb_output_init(port, i);
					break;
				} /* fallthrough */
			case DDB_OCTOPUS:
				ddb_input_init(port, 2 * i, 0, 2 * i);
				ddb_input_init(port, 2 * i + 1, 1, 2 * i + 1);
				ddb_output_init(port, i);
				break;
			case DDB_OCTOPUS_MAX:
			case DDB_OCTOPUS_MAX_CT:
			case DDB_OCTOPUS_MCI:
				ddb_input_init(port, 2 * i, 0, 2 * p);
				ddb_input_init(port, 2 * i + 1, 1, 2 * p + 1);
				break;
			default:
				break;
			}
		}
	}
	dev->port_num = p;
}