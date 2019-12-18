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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/ * PBTCDBGINFO ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BT_INFO_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXhalbtcoutsrc_DisplayBtCoexInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GLBtCoexist ; 
 int /*<<< orphan*/  GLBtcDbgInfo ; 

void hal_btcoex_DisplayBtCoexInfo(struct adapter *padapter, u8 *pbuf, u32 bufsize)
{
	PBTCDBGINFO pinfo;


	pinfo = &GLBtcDbgInfo;
	DBG_BT_INFO_INIT(pinfo, pbuf, bufsize);
	EXhalbtcoutsrc_DisplayBtCoexInfo(&GLBtCoexist);
	DBG_BT_INFO_INIT(pinfo, NULL, 0);
}