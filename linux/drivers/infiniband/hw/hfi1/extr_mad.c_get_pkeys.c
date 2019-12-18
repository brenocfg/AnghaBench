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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct hfi1_pportdata {int /*<<< orphan*/  pkeys; } ;
struct hfi1_devdata {struct hfi1_pportdata* pport; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_pkeys(struct hfi1_devdata *dd, u8 port, u16 *pkeys)
{
	struct hfi1_pportdata *ppd = dd->pport + port - 1;

	memcpy(pkeys, ppd->pkeys, sizeof(ppd->pkeys));

	return 0;
}