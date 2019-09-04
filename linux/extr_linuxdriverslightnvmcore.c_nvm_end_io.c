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
struct nvm_tgt_dev {int dummy; } ;
struct nvm_rq {int /*<<< orphan*/  (* end_io ) (struct nvm_rq*) ;struct nvm_tgt_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvm_rq_dev_to_tgt (struct nvm_tgt_dev*,struct nvm_rq*) ; 
 int /*<<< orphan*/  stub1 (struct nvm_rq*) ; 

void nvm_end_io(struct nvm_rq *rqd)
{
	struct nvm_tgt_dev *tgt_dev = rqd->dev;

	/* Convert address space */
	if (tgt_dev)
		nvm_rq_dev_to_tgt(tgt_dev, rqd);

	if (rqd->end_io)
		rqd->end_io(rqd);
}