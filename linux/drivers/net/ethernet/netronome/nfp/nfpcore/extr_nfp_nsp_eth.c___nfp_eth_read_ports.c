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
union eth_table_entry {int port; } ;
struct nfp_nsp {int dummy; } ;
struct nfp_eth_table {int count; int /*<<< orphan*/ * ports; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NSP_ETH_MAX_COUNT ; 
 int NSP_ETH_PORT_LANES_MASK ; 
 int /*<<< orphan*/  NSP_ETH_TABLE_SIZE ; 
 int /*<<< orphan*/  kfree (union eth_table_entry*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_err (struct nfp_cpp*,char*,int,...) ; 
 int /*<<< orphan*/  nfp_eth_calc_port_geometry (struct nfp_cpp*,struct nfp_eth_table*) ; 
 int /*<<< orphan*/  nfp_eth_calc_port_type (struct nfp_cpp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_eth_port_translate (struct nfp_nsp*,union eth_table_entry*,int,int /*<<< orphan*/ *) ; 
 int nfp_nsp_read_eth_table (struct nfp_nsp*,union eth_table_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ports ; 
 int /*<<< orphan*/  struct_size (struct nfp_eth_table*,int /*<<< orphan*/ ,int) ; 

struct nfp_eth_table *
__nfp_eth_read_ports(struct nfp_cpp *cpp, struct nfp_nsp *nsp)
{
	union eth_table_entry *entries;
	struct nfp_eth_table *table;
	int i, j, ret, cnt = 0;

	entries = kzalloc(NSP_ETH_TABLE_SIZE, GFP_KERNEL);
	if (!entries)
		return NULL;

	ret = nfp_nsp_read_eth_table(nsp, entries, NSP_ETH_TABLE_SIZE);
	if (ret < 0) {
		nfp_err(cpp, "reading port table failed %d\n", ret);
		goto err;
	}

	for (i = 0; i < NSP_ETH_MAX_COUNT; i++)
		if (entries[i].port & NSP_ETH_PORT_LANES_MASK)
			cnt++;

	/* Some versions of flash will give us 0 instead of port count.
	 * For those that give a port count, verify it against the value
	 * calculated above.
	 */
	if (ret && ret != cnt) {
		nfp_err(cpp, "table entry count reported (%d) does not match entries present (%d)\n",
			ret, cnt);
		goto err;
	}

	table = kzalloc(struct_size(table, ports, cnt), GFP_KERNEL);
	if (!table)
		goto err;

	table->count = cnt;
	for (i = 0, j = 0; i < NSP_ETH_MAX_COUNT; i++)
		if (entries[i].port & NSP_ETH_PORT_LANES_MASK)
			nfp_eth_port_translate(nsp, &entries[i], i,
					       &table->ports[j++]);

	nfp_eth_calc_port_geometry(cpp, table);
	for (i = 0; i < table->count; i++)
		nfp_eth_calc_port_type(cpp, &table->ports[i]);

	kfree(entries);

	return table;

err:
	kfree(entries);
	return NULL;
}