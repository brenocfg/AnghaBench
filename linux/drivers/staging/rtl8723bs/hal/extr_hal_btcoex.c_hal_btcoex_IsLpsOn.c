#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct adapter {int dummy; } ;
struct TYPE_3__ {scalar_t__ bBtLpsOn; scalar_t__ bBtDisabled; } ;
struct TYPE_4__ {TYPE_1__ btInfo; } ;

/* Variables and functions */
 TYPE_2__ GLBtCoexist ; 
 int /*<<< orphan*/  hal_btcoex_IsBtExist (struct adapter*) ; 

bool hal_btcoex_IsLpsOn(struct adapter *padapter)
{
	if (!hal_btcoex_IsBtExist(padapter))
		return false;

	if (GLBtCoexist.btInfo.bBtDisabled)
		return false;

	if (GLBtCoexist.btInfo.bBtLpsOn)
		return true;

	return false;
}