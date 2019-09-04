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
struct TYPE_2__ {int /*<<< orphan*/  pt; } ;
struct saa7134_dev {TYPE_1__ ts_q; int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  saa7134_pgtable_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int saa7134_ts_fini(struct saa7134_dev *dev)
{
	saa7134_pgtable_free(dev->pci, &dev->ts_q.pt);
	return 0;
}