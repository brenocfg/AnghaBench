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
struct seq_file {struct mvpp2_port* private; } ;
struct mvpp2_prs_entry {int dummy; } ;
struct mvpp2_port {int /*<<< orphan*/  id; struct mvpp2* priv; } ;
struct mvpp2 {TYPE_1__* prs_shadow; } ;
struct TYPE_2__ {scalar_t__ valid; } ;

/* Variables and functions */
 int MVPP2_PRS_TCAM_SRAM_SIZE ; 
 int /*<<< orphan*/  mvpp2_prs_init_from_hw (struct mvpp2*,struct mvpp2_prs_entry*,int) ; 
 unsigned long mvpp2_prs_tcam_port_map_get (struct mvpp2_prs_entry*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int mvpp2_dbgfs_port_parser_show(struct seq_file *s, void *unused)
{
	struct mvpp2_port *port = s->private;
	struct mvpp2 *priv = port->priv;
	struct mvpp2_prs_entry pe;
	unsigned long pmap;
	int i;

	for (i = 0; i < MVPP2_PRS_TCAM_SRAM_SIZE; i++) {
		mvpp2_prs_init_from_hw(port->priv, &pe, i);

		pmap = mvpp2_prs_tcam_port_map_get(&pe);
		if (priv->prs_shadow[i].valid && test_bit(port->id, &pmap))
			seq_printf(s, "%03d\n", i);
	}

	return 0;
}