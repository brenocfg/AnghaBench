#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ len; scalar_t__ size; int /*<<< orphan*/ * info; } ;
typedef  TYPE_1__* PBTCDBGINFO ;

/* Variables and functions */
 TYPE_1__ GLBtcDbgInfo ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

void DBG_BT_INFO(u8 *dbgmsg)
{
	PBTCDBGINFO pinfo;
	u32 msglen;
	u8 *pbuf;


	pinfo = &GLBtcDbgInfo;

	if (!pinfo->info)
		return;

	msglen = strlen(dbgmsg);
	if (pinfo->len + msglen > pinfo->size)
		return;

	pbuf = pinfo->info + pinfo->len;
	memcpy(pbuf, dbgmsg, msglen);
	pinfo->len += msglen;
}