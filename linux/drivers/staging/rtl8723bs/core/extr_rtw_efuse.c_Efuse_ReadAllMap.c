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
typedef  scalar_t__ u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_GetEfuseDefinition (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  Efuse_PowerSwitch (struct adapter*,int,int) ; 
 int /*<<< orphan*/  TYPE_EFUSE_MAP_LEN ; 
 int /*<<< orphan*/  efuse_ReadEFuse (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 

void
Efuse_ReadAllMap(
	struct adapter *padapter,
	u8 efuseType,
	u8 *Efuse,
	bool		bPseudoTest)
{
	u16 mapLen = 0;

	Efuse_PowerSwitch(padapter, false, true);

	EFUSE_GetEfuseDefinition(padapter, efuseType, TYPE_EFUSE_MAP_LEN, (void *)&mapLen, bPseudoTest);

	efuse_ReadEFuse(padapter, efuseType, 0, mapLen, Efuse, bPseudoTest);

	Efuse_PowerSwitch(padapter, false, false);
}