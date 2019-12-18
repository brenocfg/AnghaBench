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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int (* Efuse_PgPacketRead ) (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;
struct adapter {TYPE_1__ HalFunc; } ;

/* Variables and functions */
 int stub1 (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int
Efuse_PgPacketRead(struct adapter *padapter,
				u8 	offset,
				u8 	*data,
				bool		bPseudoTest)
{
	return padapter->HalFunc.Efuse_PgPacketRead(padapter, offset, data,
						    bPseudoTest);
}