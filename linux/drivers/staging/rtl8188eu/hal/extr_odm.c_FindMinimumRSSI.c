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
struct dm_priv {int /*<<< orphan*/  EntryMinUndecoratedSmoothedPWDB; int /*<<< orphan*/  MinUndecoratedPWDBForDM; } ;
struct adapter {TYPE_1__* HalData; } ;
struct TYPE_2__ {struct dm_priv dmpriv; } ;

/* Variables and functions */

__attribute__((used)) static void FindMinimumRSSI(struct adapter *pAdapter)
{
	struct dm_priv	*pdmpriv = &pAdapter->HalData->dmpriv;

	/* 1 1.Unconditionally set RSSI */
	pdmpriv->MinUndecoratedPWDBForDM = pdmpriv->EntryMinUndecoratedSmoothedPWDB;
}