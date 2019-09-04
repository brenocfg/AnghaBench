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

/* Variables and functions */

__attribute__((used)) static void show_saved_mc(void)
{
#ifdef DEBUG
	int i = 0, j;
	unsigned int sig, pf, rev, total_size, data_size, date;
	struct ucode_cpu_info uci;
	struct ucode_patch *p;

	if (list_empty(&microcode_cache)) {
		pr_debug("no microcode data saved.\n");
		return;
	}

	collect_cpu_info_early(&uci);

	sig	= uci.cpu_sig.sig;
	pf	= uci.cpu_sig.pf;
	rev	= uci.cpu_sig.rev;
	pr_debug("CPU: sig=0x%x, pf=0x%x, rev=0x%x\n", sig, pf, rev);

	list_for_each_entry(p, &microcode_cache, plist) {
		struct microcode_header_intel *mc_saved_header;
		struct extended_sigtable *ext_header;
		struct extended_signature *ext_sig;
		int ext_sigcount;

		mc_saved_header = (struct microcode_header_intel *)p->data;

		sig	= mc_saved_header->sig;
		pf	= mc_saved_header->pf;
		rev	= mc_saved_header->rev;
		date	= mc_saved_header->date;

		total_size	= get_totalsize(mc_saved_header);
		data_size	= get_datasize(mc_saved_header);

		pr_debug("mc_saved[%d]: sig=0x%x, pf=0x%x, rev=0x%x, total size=0x%x, date = %04x-%02x-%02x\n",
			 i++, sig, pf, rev, total_size,
			 date & 0xffff,
			 date >> 24,
			 (date >> 16) & 0xff);

		/* Look for ext. headers: */
		if (total_size <= data_size + MC_HEADER_SIZE)
			continue;

		ext_header = (void *)mc_saved_header + data_size + MC_HEADER_SIZE;
		ext_sigcount = ext_header->count;
		ext_sig = (void *)ext_header + EXT_HEADER_SIZE;

		for (j = 0; j < ext_sigcount; j++) {
			sig = ext_sig->sig;
			pf = ext_sig->pf;

			pr_debug("\tExtended[%d]: sig=0x%x, pf=0x%x\n",
				 j, sig, pf);

			ext_sig++;
		}
	}
#endif
}