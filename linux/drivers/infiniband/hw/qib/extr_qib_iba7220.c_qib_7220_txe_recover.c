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
struct qib_devdata {int /*<<< orphan*/  pport; int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  qib_devinfo (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qib_disarm_7220_senderrbufs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qib_7220_txe_recover(struct qib_devdata *dd)
{
	qib_devinfo(dd->pcidev, "Recovering from TXE PIO parity error\n");
	qib_disarm_7220_senderrbufs(dd->pport);
}