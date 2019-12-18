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
struct rvu {int dummy; } ;
struct msg_rsp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcifunc; } ;
struct msg_req {TYPE_1__ hdr; } ;

/* Variables and functions */
 int nix_get_nixlf (struct rvu*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rvu_npc_enable_default_entries (struct rvu*,int /*<<< orphan*/ ,int) ; 

int rvu_mbox_handler_nix_lf_start_rx(struct rvu *rvu, struct msg_req *req,
				     struct msg_rsp *rsp)
{
	u16 pcifunc = req->hdr.pcifunc;
	int nixlf, err;

	err = nix_get_nixlf(rvu, pcifunc, &nixlf);
	if (err)
		return err;

	rvu_npc_enable_default_entries(rvu, pcifunc, nixlf);
	return 0;
}