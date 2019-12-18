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
typedef  int /*<<< orphan*/  u16 ;
struct mvpp2_port {struct mvpp2* priv; } ;
struct mvpp2 {TYPE_1__* prs_shadow; } ;
struct TYPE_2__ {int valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvpp2_prs_hw_inv (struct mvpp2*,int) ; 
 int mvpp2_prs_vid_range_find (struct mvpp2_port*,int /*<<< orphan*/ ,int) ; 

void mvpp2_prs_vid_entry_remove(struct mvpp2_port *port, u16 vid)
{
	struct mvpp2 *priv = port->priv;
	int tid;

	/* Scan TCAM and see if entry with this <vid,port> already exist */
	tid = mvpp2_prs_vid_range_find(port, vid, 0xfff);

	/* No such entry */
	if (tid < 0)
		return;

	mvpp2_prs_hw_inv(priv, tid);
	priv->prs_shadow[tid].valid = false;
}