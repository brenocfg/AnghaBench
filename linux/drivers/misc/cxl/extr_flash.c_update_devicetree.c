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
typedef  int u32 ;
struct update_nodes_workarea {int /*<<< orphan*/  unit_address; } ;
struct cxl {TYPE_1__* guest; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NODE_ACTION_MASK ; 
 int NODE_COUNT_MASK ; 
#define  OPCODE_ADD 130 
#define  OPCODE_DELETE 129 
#define  OPCODE_UPDATE 128 
 int /*<<< orphan*/  RTAS_DATA_BUF_SIZE ; 
 int RTAS_UNKNOWN_SERVICE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_devel (char*,int,int) ; 
 int rcall (int,char*,int /*<<< orphan*/ ) ; 
 int rtas_token (char*) ; 
 int /*<<< orphan*/  update_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_devicetree(struct cxl *adapter, s32 scope)
{
	struct update_nodes_workarea *unwa;
	u32 action, node_count;
	int token, rc, i;
	__be32 *data, drc_index, phandle;
	char *buf;

	token = rtas_token("ibm,update-nodes");
	if (token == RTAS_UNKNOWN_SERVICE)
		return -EINVAL;

	buf = kzalloc(RTAS_DATA_BUF_SIZE, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	unwa = (struct update_nodes_workarea *)&buf[0];
	unwa->unit_address = cpu_to_be64(adapter->guest->handle);
	do {
		rc = rcall(token, buf, scope);
		if (rc && rc != 1)
			break;

		data = (__be32 *)buf + 4;
		while (be32_to_cpu(*data) & NODE_ACTION_MASK) {
			action = be32_to_cpu(*data) & NODE_ACTION_MASK;
			node_count = be32_to_cpu(*data) & NODE_COUNT_MASK;
			pr_devel("device reconfiguration - action: %#x, nodes: %#x\n",
				 action, node_count);
			data++;

			for (i = 0; i < node_count; i++) {
				phandle = *data++;

				switch (action) {
				case OPCODE_DELETE:
					/* nothing to do */
					break;
				case OPCODE_UPDATE:
					update_node(phandle, scope);
					break;
				case OPCODE_ADD:
					/* nothing to do, just move pointer */
					drc_index = *data++;
					break;
				}
			}
		}
	} while (rc == 1);

	kfree(buf);
	return 0;
}