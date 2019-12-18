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
struct rvu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcifunc; } ;
struct nix_txsch_free_req {int flags; TYPE_1__ hdr; } ;
struct msg_rsp {int dummy; } ;

/* Variables and functions */
 int TXSCHQ_FREE_ALL ; 
 int nix_txschq_free (struct rvu*,int /*<<< orphan*/ ) ; 
 int nix_txschq_free_one (struct rvu*,struct nix_txsch_free_req*) ; 

int rvu_mbox_handler_nix_txsch_free(struct rvu *rvu,
				    struct nix_txsch_free_req *req,
				    struct msg_rsp *rsp)
{
	if (req->flags & TXSCHQ_FREE_ALL)
		return nix_txschq_free(rvu, req->hdr.pcifunc);
	else
		return nix_txschq_free_one(rvu, req);
}