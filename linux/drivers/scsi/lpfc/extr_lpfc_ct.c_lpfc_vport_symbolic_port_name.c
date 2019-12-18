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
struct lpfc_vport {TYPE_1__* phba; } ;
struct TYPE_2__ {int /*<<< orphan*/  brd_no; } ;

/* Variables and functions */
 int scnprintf (char*,size_t,char*,int /*<<< orphan*/ ) ; 

int
lpfc_vport_symbolic_port_name(struct lpfc_vport *vport, char *symbol,
	size_t size)
{
	int n;

	/*
	 * Use the lpfc board number as the Symbolic Port
	 * Name object.  NPIV is not in play so this integer
	 * value is sufficient and unique per FC-ID.
	 */
	n = scnprintf(symbol, size, "%d", vport->phba->brd_no);
	return n;
}