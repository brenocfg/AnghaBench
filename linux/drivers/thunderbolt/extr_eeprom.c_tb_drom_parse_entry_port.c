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
struct TYPE_3__ {size_t max_port_number; } ;
struct tb_switch {struct tb_port* ports; int /*<<< orphan*/  dev; TYPE_1__ config; } ;
struct tb_port {TYPE_2__* sw; int /*<<< orphan*/ * dual_link_port; int /*<<< orphan*/  link_nr; scalar_t__ disabled; } ;
struct tb_drom_entry_port {size_t dual_link_port_nr; scalar_t__ has_dual_link_port; int /*<<< orphan*/  link_nr; } ;
struct tb_drom_entry_header {size_t index; int len; scalar_t__ port_disabled; } ;
typedef  enum tb_port_type { ____Placeholder_tb_port_type } tb_port_type ;
struct TYPE_4__ {int /*<<< orphan*/ * ports; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  TB_CFG_PORT ; 
 int TB_TYPE_PORT ; 
 int /*<<< orphan*/  dev_info_once (int /*<<< orphan*/ *,char*) ; 
 int tb_port_read (struct tb_port*,int*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tb_sw_warn (struct tb_switch*,char*,int,int) ; 

__attribute__((used)) static int tb_drom_parse_entry_port(struct tb_switch *sw,
				    struct tb_drom_entry_header *header)
{
	struct tb_port *port;
	int res;
	enum tb_port_type type;

	/*
	 * Some DROMs list more ports than the controller actually has
	 * so we skip those but allow the parser to continue.
	 */
	if (header->index > sw->config.max_port_number) {
		dev_info_once(&sw->dev, "ignoring unnecessary extra entries in DROM\n");
		return 0;
	}

	port = &sw->ports[header->index];
	port->disabled = header->port_disabled;
	if (port->disabled)
		return 0;

	res = tb_port_read(port, &type, TB_CFG_PORT, 2, 1);
	if (res)
		return res;
	type &= 0xffffff;

	if (type == TB_TYPE_PORT) {
		struct tb_drom_entry_port *entry = (void *) header;
		if (header->len != sizeof(*entry)) {
			tb_sw_warn(sw,
				"port entry has size %#x (expected %#zx)\n",
				header->len, sizeof(struct tb_drom_entry_port));
			return -EIO;
		}
		port->link_nr = entry->link_nr;
		if (entry->has_dual_link_port)
			port->dual_link_port =
				&port->sw->ports[entry->dual_link_port_nr];
	}
	return 0;
}