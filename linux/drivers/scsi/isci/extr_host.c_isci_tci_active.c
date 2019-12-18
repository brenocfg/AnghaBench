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
struct isci_host {int /*<<< orphan*/  tci_tail; int /*<<< orphan*/  tci_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIRC_CNT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_MAX_IO_REQUESTS ; 

__attribute__((used)) static u16 isci_tci_active(struct isci_host *ihost)
{
	return CIRC_CNT(ihost->tci_head, ihost->tci_tail, SCI_MAX_IO_REQUESTS);
}