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
typedef  unsigned char u16 ;
struct seq_file {struct mvpp2_port* private; } ;
struct mvpp2_prs_entry {int dummy; } ;
struct mvpp2_port {int /*<<< orphan*/  id; struct mvpp2* priv; } ;
struct mvpp2 {TYPE_1__* prs_shadow; } ;
struct TYPE_2__ {int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int MVPP2_PRS_VID_PORT_FIRST (int /*<<< orphan*/ ) ; 
 int MVPP2_PRS_VID_PORT_LAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_init_from_hw (struct mvpp2*,struct mvpp2_prs_entry*,int) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_data_byte_get (struct mvpp2_prs_entry*,int,unsigned char*,unsigned char*) ; 
 unsigned long mvpp2_prs_tcam_port_map_get (struct mvpp2_prs_entry*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned char) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int mvpp2_dbgfs_port_vid_show(struct seq_file *s, void *unused)
{
	struct mvpp2_port *port = s->private;
	unsigned char byte[2], enable[2];
	struct mvpp2 *priv = port->priv;
	struct mvpp2_prs_entry pe;
	unsigned long pmap;
	u16 rvid;
	int tid;

	for (tid = MVPP2_PRS_VID_PORT_FIRST(port->id);
	     tid <= MVPP2_PRS_VID_PORT_LAST(port->id); tid++) {
		mvpp2_prs_init_from_hw(priv, &pe, tid);

		pmap = mvpp2_prs_tcam_port_map_get(&pe);

		if (!priv->prs_shadow[tid].valid)
			continue;

		if (!test_bit(port->id, &pmap))
			continue;

		mvpp2_prs_tcam_data_byte_get(&pe, 2, &byte[0], &enable[0]);
		mvpp2_prs_tcam_data_byte_get(&pe, 3, &byte[1], &enable[1]);

		rvid = ((byte[0] & 0xf) << 8) + byte[1];

		seq_printf(s, "%u\n", rvid);
	}

	return 0;
}