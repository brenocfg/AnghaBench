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
struct mmc_request {int tag; scalar_t__ cmd; } ;

/* Variables and functions */
 int DCMD_SLOT ; 

__attribute__((used)) static inline int cqhci_tag(struct mmc_request *mrq)
{
	return mrq->cmd ? DCMD_SLOT : mrq->tag;
}