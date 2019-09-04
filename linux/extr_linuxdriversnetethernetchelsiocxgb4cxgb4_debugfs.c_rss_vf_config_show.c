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
struct seq_file {int dummy; } ;
struct rss_vf_conf {int rss_vf_vfh; int /*<<< orphan*/  rss_vf_vfl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULTQUEUE_G (int) ; 
 int ENABLEUDPHASH_F ; 
 int /*<<< orphan*/  KEYINDEX_G (int) ; 
 void* SEQ_START_TOKEN ; 
 int VFCHNEN_F ; 
 int VFIP4FOURTUPEN_F ; 
 int VFIP4TWOTUPEN_F ; 
 int VFIP6TWOTUPEN_F ; 
 int /*<<< orphan*/  VFLKPIDX_G (int) ; 
 int VFPRTEN_F ; 
 int VFUPEN_F ; 
 int VFVLNEX_F ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  yesno (int) ; 

__attribute__((used)) static int rss_vf_config_show(struct seq_file *seq, void *v, int idx)
{
	if (v == SEQ_START_TOKEN) {
		seq_puts(seq, "     RSS                     Hash Tuple Enable\n");
		seq_puts(seq, "     Enable   IVF  Dis  Enb  IPv6      IPv4      UDP    Def  Secret Key\n");
		seq_puts(seq, " VF  Chn Prt  Map  VLAN  uP  Four Two  Four Two  Four   Que  Idx       Hash\n");
	} else {
		struct rss_vf_conf *vfconf = v;

		seq_printf(seq, "%3d  %3s %3s  %3d   %3s %3s   %3s %3s   %3s  %3s   %3s  %4d  %3d %#10x\n",
			   idx,
			   yesno(vfconf->rss_vf_vfh & VFCHNEN_F),
			   yesno(vfconf->rss_vf_vfh & VFPRTEN_F),
			   VFLKPIDX_G(vfconf->rss_vf_vfh),
			   yesno(vfconf->rss_vf_vfh & VFVLNEX_F),
			   yesno(vfconf->rss_vf_vfh & VFUPEN_F),
			   yesno(vfconf->rss_vf_vfh & VFIP4FOURTUPEN_F),
			   yesno(vfconf->rss_vf_vfh & VFIP6TWOTUPEN_F),
			   yesno(vfconf->rss_vf_vfh & VFIP4FOURTUPEN_F),
			   yesno(vfconf->rss_vf_vfh & VFIP4TWOTUPEN_F),
			   yesno(vfconf->rss_vf_vfh & ENABLEUDPHASH_F),
			   DEFAULTQUEUE_G(vfconf->rss_vf_vfh),
			   KEYINDEX_G(vfconf->rss_vf_vfh),
			   vfconf->rss_vf_vfl);
	}
	return 0;
}