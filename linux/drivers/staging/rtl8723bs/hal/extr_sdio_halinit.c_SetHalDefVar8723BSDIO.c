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
struct adapter {int dummy; } ;
typedef  enum HAL_DEF_VARIABLE { ____Placeholder_HAL_DEF_VARIABLE } HAL_DEF_VARIABLE ;

/* Variables and functions */
 int /*<<< orphan*/  SetHalDefVar8723B (struct adapter*,int,void*) ; 

__attribute__((used)) static u8 SetHalDefVar8723BSDIO(struct adapter *Adapter,
				enum HAL_DEF_VARIABLE eVariable, void *pValue)
{
	return SetHalDefVar8723B(Adapter, eVariable, pValue);
}