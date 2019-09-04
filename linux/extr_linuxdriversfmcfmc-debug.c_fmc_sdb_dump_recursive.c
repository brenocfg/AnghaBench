#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int record_type; } ;
struct TYPE_7__ {int commit_id; int /*<<< orphan*/  tool_version; int /*<<< orphan*/  tool_name; int /*<<< orphan*/  user_name; int /*<<< orphan*/  date; int /*<<< orphan*/  syn_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  repo_url; } ;
struct sdb_product {int /*<<< orphan*/  name; int /*<<< orphan*/  device_id; int /*<<< orphan*/  vendor_id; } ;
struct sdb_component {int /*<<< orphan*/  addr_first; int /*<<< orphan*/  addr_last; struct sdb_product product; } ;
struct TYPE_5__ {struct sdb_component sdb_component; } ;
union sdb_record {TYPE_4__ empty; TYPE_3__ synthesis; TYPE_2__ repo_url; TYPE_1__ dev; } ;
struct seq_file {int dummy; } ;
struct sdb_array {unsigned long baseaddr; int len; int level; struct sdb_array** subtree; union sdb_record* record; } ;
struct fmc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct sdb_array*) ; 
 int PTR_ERR (struct sdb_array*) ; 
 int /*<<< orphan*/  __be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __be64_to_cpu (int /*<<< orphan*/ ) ; 
 int __sdb_string (char*,int /*<<< orphan*/ ) ; 
#define  sdb_type_bridge 134 
#define  sdb_type_device 133 
#define  sdb_type_empty 132 
#define  sdb_type_integration 131 
#define  sdb_type_interconnect 130 
#define  sdb_type_repo_url 129 
#define  sdb_type_synthesis 128 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void fmc_sdb_dump_recursive(struct fmc_device *fmc, struct seq_file *s,
				   const struct sdb_array *arr)
{
	unsigned long base = arr->baseaddr;
	int i, j, n = arr->len, level = arr->level;
	char tmp[64];

	for (i = 0; i < n; i++) {
		union  sdb_record *r;
		struct sdb_product *p;
		struct sdb_component *c;

		r = &arr->record[i];
		c = &r->dev.sdb_component;
		p = &c->product;

		for (j = 0; j < level; j++)
			seq_printf(s, "   ");
		switch (r->empty.record_type) {
		case sdb_type_interconnect:
			seq_printf(s, "%08llx:%08x %.19s\n",
				   __be64_to_cpu(p->vendor_id),
				   __be32_to_cpu(p->device_id),
				   p->name);
			break;
		case sdb_type_device:
			seq_printf(s, "%08llx:%08x %.19s (%08llx-%08llx)\n",
				   __be64_to_cpu(p->vendor_id),
				   __be32_to_cpu(p->device_id),
				   p->name,
				   __be64_to_cpu(c->addr_first) + base,
				   __be64_to_cpu(c->addr_last) + base);
			break;
		case sdb_type_bridge:
			seq_printf(s, "%08llx:%08x %.19s (bridge: %08llx)\n",
				   __be64_to_cpu(p->vendor_id),
				   __be32_to_cpu(p->device_id),
				   p->name,
				   __be64_to_cpu(c->addr_first) + base);
			if (IS_ERR(arr->subtree[i])) {
				seq_printf(s, "SDB: (bridge error %li)\n",
					 PTR_ERR(arr->subtree[i]));
				break;
			}
			fmc_sdb_dump_recursive(fmc, s, arr->subtree[i]);
			break;
		case sdb_type_integration:
			seq_printf(s, "integration\n");
			break;
		case sdb_type_repo_url:
			seq_printf(s, "Synthesis repository: %s\n",
					  __sdb_string(tmp, r->repo_url.repo_url));
			break;
		case sdb_type_synthesis:
			seq_printf(s, "Bitstream '%s' ",
					  __sdb_string(tmp, r->synthesis.syn_name));
			seq_printf(s, "synthesized %08x by %s ",
					  __be32_to_cpu(r->synthesis.date),
					  __sdb_string(tmp, r->synthesis.user_name));
			seq_printf(s, "(%s version %x), ",
					  __sdb_string(tmp, r->synthesis.tool_name),
					  __be32_to_cpu(r->synthesis.tool_version));
			seq_printf(s, "commit %pm\n",
					  r->synthesis.commit_id);
			break;
		case sdb_type_empty:
			seq_printf(s, "empty\n");
			break;
		default:
			seq_printf(s, "UNKNOWN TYPE 0x%02x\n",
				   r->empty.record_type);
			break;
		}
	}
}