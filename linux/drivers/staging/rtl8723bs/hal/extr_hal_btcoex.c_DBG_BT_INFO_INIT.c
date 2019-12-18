#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/ * info; } ;
typedef  TYPE_1__* PBTCDBGINFO ;
typedef  int /*<<< orphan*/  BTCDBGINFO ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void DBG_BT_INFO_INIT(PBTCDBGINFO pinfo, u8 *pbuf, u32 size)
{
	if (!pinfo)
		return;

	memset(pinfo, 0, sizeof(BTCDBGINFO));

	if (pbuf && size) {
		pinfo->info = pbuf;
		pinfo->size = size;
	}
}