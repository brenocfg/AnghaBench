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
struct seq_file {struct adapter* private; } ;
struct cudbg_meminfo {int avail_c; int mem_c; int /*<<< orphan*/ * loopback_alloc; int /*<<< orphan*/ * loopback_used; int /*<<< orphan*/ * port_alloc; int /*<<< orphan*/ * port_used; int /*<<< orphan*/  p_structs_free_cnt; int /*<<< orphan*/  p_structs; int /*<<< orphan*/ * tx_pages_data; int /*<<< orphan*/  free_tx_cnt; int /*<<< orphan*/ * rx_pages_data; int /*<<< orphan*/  free_rx_cnt; scalar_t__ up_extmem2_hi; scalar_t__ up_extmem2_lo; scalar_t__ up_ram_hi; scalar_t__ up_ram_lo; TYPE_2__* mem; TYPE_1__* avail; } ;
struct TYPE_7__ {int nchan; } ;
struct TYPE_8__ {TYPE_3__ arch; } ;
struct adapter {TYPE_4__ params; } ;
struct TYPE_6__ {size_t idx; scalar_t__ limit; scalar_t__ base; } ;
struct TYPE_5__ {size_t idx; scalar_t__ limit; scalar_t__ base; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 int ENXIO ; 
 int cudbg_fill_meminfo (struct adapter*,struct cudbg_meminfo*) ; 
 char** cudbg_region ; 
 int /*<<< orphan*/  mem_region_show (struct seq_file*,char const* const,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct cudbg_meminfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static int meminfo_show(struct seq_file *seq, void *v)
{
	static const char * const memory[] = { "EDC0:", "EDC1:", "MC:",
					       "MC0:", "MC1:", "HMA:"};
	struct adapter *adap = seq->private;
	struct cudbg_meminfo meminfo;
	int i, rc;

	memset(&meminfo, 0, sizeof(struct cudbg_meminfo));
	rc = cudbg_fill_meminfo(adap, &meminfo);
	if (rc)
		return -ENXIO;

	for (i = 0; i < meminfo.avail_c; i++)
		mem_region_show(seq, memory[meminfo.avail[i].idx],
				meminfo.avail[i].base,
				meminfo.avail[i].limit - 1);

	seq_putc(seq, '\n');
	for (i = 0; i < meminfo.mem_c; i++) {
		if (meminfo.mem[i].idx >= ARRAY_SIZE(cudbg_region))
			continue;                        /* skip holes */
		if (!meminfo.mem[i].limit)
			meminfo.mem[i].limit =
				i < meminfo.mem_c - 1 ?
				meminfo.mem[i + 1].base - 1 : ~0;
		mem_region_show(seq, cudbg_region[meminfo.mem[i].idx],
				meminfo.mem[i].base, meminfo.mem[i].limit);
	}

	seq_putc(seq, '\n');
	mem_region_show(seq, "uP RAM:", meminfo.up_ram_lo, meminfo.up_ram_hi);
	mem_region_show(seq, "uP Extmem2:", meminfo.up_extmem2_lo,
			meminfo.up_extmem2_hi);

	seq_printf(seq, "\n%u Rx pages (%u free) of size %uKiB for %u channels\n",
		   meminfo.rx_pages_data[0], meminfo.free_rx_cnt,
		   meminfo.rx_pages_data[1], meminfo.rx_pages_data[2]);

	seq_printf(seq, "%u Tx pages (%u free) of size %u%ciB for %u channels\n",
		   meminfo.tx_pages_data[0], meminfo.free_tx_cnt,
		   meminfo.tx_pages_data[1], meminfo.tx_pages_data[2],
		   meminfo.tx_pages_data[3]);

	seq_printf(seq, "%u p-structs (%u free)\n\n",
		   meminfo.p_structs, meminfo.p_structs_free_cnt);

	for (i = 0; i < 4; i++)
		/* For T6 these are MAC buffer groups */
		seq_printf(seq, "Port %d using %u pages out of %u allocated\n",
			   i, meminfo.port_used[i], meminfo.port_alloc[i]);

	for (i = 0; i < adap->params.arch.nchan; i++)
		/* For T6 these are MAC buffer groups */
		seq_printf(seq,
			   "Loopback %d using %u pages out of %u allocated\n",
			   i, meminfo.loopback_used[i],
			   meminfo.loopback_alloc[i]);

	return 0;
}