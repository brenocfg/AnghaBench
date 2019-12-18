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
typedef  unsigned char u16 ;
struct mvpp2_prs_entry {int dummy; } ;
struct mvpp2_port {TYPE_2__* priv; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__* prs_shadow; } ;
struct TYPE_3__ {scalar_t__ lu; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ MVPP2_PRS_LU_VID ; 
 int MVPP2_PRS_VID_PORT_FIRST (int /*<<< orphan*/ ) ; 
 int MVPP2_PRS_VID_PORT_LAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_init_from_hw (TYPE_2__*,struct mvpp2_prs_entry*,int) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_data_byte_get (struct mvpp2_prs_entry*,int,unsigned char*,unsigned char*) ; 

__attribute__((used)) static int mvpp2_prs_vid_range_find(struct mvpp2_port *port, u16 vid, u16 mask)
{
	unsigned char byte[2], enable[2];
	struct mvpp2_prs_entry pe;
	u16 rvid, rmask;
	int tid;

	/* Go through the all entries with MVPP2_PRS_LU_VID */
	for (tid = MVPP2_PRS_VID_PORT_FIRST(port->id);
	     tid <= MVPP2_PRS_VID_PORT_LAST(port->id); tid++) {
		if (!port->priv->prs_shadow[tid].valid ||
		    port->priv->prs_shadow[tid].lu != MVPP2_PRS_LU_VID)
			continue;

		mvpp2_prs_init_from_hw(port->priv, &pe, tid);

		mvpp2_prs_tcam_data_byte_get(&pe, 2, &byte[0], &enable[0]);
		mvpp2_prs_tcam_data_byte_get(&pe, 3, &byte[1], &enable[1]);

		rvid = ((byte[0] & 0xf) << 8) + byte[1];
		rmask = ((enable[0] & 0xf) << 8) + enable[1];

		if (rvid != vid || rmask != mask)
			continue;

		return tid;
	}

	return -ENOENT;
}