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
struct scb {int flags; int* seqctl; int seqctl_nonqos; int /*<<< orphan*/  magic; scalar_t__* seqnum; } ;

/* Variables and functions */
 int NUMPRIO ; 
 int SCB_HTCAP ; 
 int /*<<< orphan*/  SCB_MAGIC ; 
 int SCB_WMECAP ; 
 int /*<<< orphan*/  memset (struct scb*,int /*<<< orphan*/ ,int) ; 

void brcms_c_init_scb(struct scb *scb)
{
	int i;

	memset(scb, 0, sizeof(struct scb));
	scb->flags = SCB_WMECAP | SCB_HTCAP;
	for (i = 0; i < NUMPRIO; i++) {
		scb->seqnum[i] = 0;
		scb->seqctl[i] = 0xFFFF;
	}

	scb->seqctl_nonqos = 0xFFFF;
	scb->magic = SCB_MAGIC;
}