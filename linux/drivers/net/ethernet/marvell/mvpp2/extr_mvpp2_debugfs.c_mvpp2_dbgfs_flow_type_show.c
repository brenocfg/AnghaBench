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
struct seq_file {struct mvpp2_dbgfs_flow_entry* private; } ;
struct mvpp2_dbgfs_flow_entry {int /*<<< orphan*/  flow; } ;
struct mvpp2_cls_flow {int flow_type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IPV4_FLOW 133 
#define  IPV6_FLOW 132 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 struct mvpp2_cls_flow* mvpp2_cls_flow_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*) ; 

__attribute__((used)) static int mvpp2_dbgfs_flow_type_show(struct seq_file *s, void *unused)
{
	struct mvpp2_dbgfs_flow_entry *entry = s->private;
	const struct mvpp2_cls_flow *f;
	const char *flow_name;

	f = mvpp2_cls_flow_get(entry->flow);
	if (!f)
		return -EINVAL;

	switch (f->flow_type) {
	case IPV4_FLOW:
		flow_name = "ipv4";
		break;
	case IPV6_FLOW:
		flow_name = "ipv6";
		break;
	case TCP_V4_FLOW:
		flow_name = "tcp4";
		break;
	case TCP_V6_FLOW:
		flow_name = "tcp6";
		break;
	case UDP_V4_FLOW:
		flow_name = "udp4";
		break;
	case UDP_V6_FLOW:
		flow_name = "udp6";
		break;
	default:
		flow_name = "other";
	}

	seq_printf(s, "%s\n", flow_name);

	return 0;
}