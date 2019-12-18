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
typedef  int /*<<< orphan*/  u16 ;
struct rvu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  npc_enadis_default_entries (struct rvu*,int /*<<< orphan*/ ,int,int) ; 

void rvu_npc_disable_default_entries(struct rvu *rvu, u16 pcifunc, int nixlf)
{
	npc_enadis_default_entries(rvu, pcifunc, nixlf, false);
}