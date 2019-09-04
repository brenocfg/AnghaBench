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
struct mmc_request {TYPE_1__* data; } ;
struct cvm_mmc_host {int /*<<< orphan*/  smi; } ;
struct TYPE_2__ {int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;

/* Variables and functions */
 int SG_MITER_ATOMIC ; 
 int SG_MITER_TO_SG ; 
 int /*<<< orphan*/  sg_miter_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void do_read_request(struct cvm_mmc_host *host, struct mmc_request *mrq)
{
	sg_miter_start(&host->smi, mrq->data->sg, mrq->data->sg_len,
		       SG_MITER_ATOMIC | SG_MITER_TO_SG);
}