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
struct TYPE_2__ {int fw_query_complete; int /*<<< orphan*/  max_rit_size; int /*<<< orphan*/  num_mcmac; int /*<<< orphan*/  num_ucmac; int /*<<< orphan*/  num_rxp; int /*<<< orphan*/  num_txq; } ;
struct bna_ioceth {TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_ENET_DEF_RITSZ ; 
 int /*<<< orphan*/  BFI_ENET_DEF_RXP ; 
 int /*<<< orphan*/  BFI_ENET_DEF_TXQ ; 
 int /*<<< orphan*/  BFI_ENET_DEF_UCAM ; 
 int /*<<< orphan*/  BFI_ENET_MAX_MCAM ; 

__attribute__((used)) static void bna_attr_init(struct bna_ioceth *ioceth)
{
	ioceth->attr.num_txq = BFI_ENET_DEF_TXQ;
	ioceth->attr.num_rxp = BFI_ENET_DEF_RXP;
	ioceth->attr.num_ucmac = BFI_ENET_DEF_UCAM;
	ioceth->attr.num_mcmac = BFI_ENET_MAX_MCAM;
	ioceth->attr.max_rit_size = BFI_ENET_DEF_RITSZ;
	ioceth->attr.fw_query_complete = false;
}