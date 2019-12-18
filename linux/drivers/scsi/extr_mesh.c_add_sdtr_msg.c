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
struct mesh_state {int n_msgout; int* msgout; int /*<<< orphan*/  conn_tgt; } ;

/* Variables and functions */
 scalar_t__ ALLOW_SYNC (int /*<<< orphan*/ ) ; 
 int EXTENDED_MESSAGE ; 
 int EXTENDED_SDTR ; 
 int mesh_sync_offset ; 
 int mesh_sync_period ; 

__attribute__((used)) static inline void add_sdtr_msg(struct mesh_state *ms)
{
	int i = ms->n_msgout;

	ms->msgout[i] = EXTENDED_MESSAGE;
	ms->msgout[i+1] = 3;
	ms->msgout[i+2] = EXTENDED_SDTR;
	ms->msgout[i+3] = mesh_sync_period/4;
	ms->msgout[i+4] = (ALLOW_SYNC(ms->conn_tgt)? mesh_sync_offset: 0);
	ms->n_msgout = i + 5;
}