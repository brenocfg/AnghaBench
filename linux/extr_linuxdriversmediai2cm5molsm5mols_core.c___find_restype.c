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
typedef  scalar_t__ u32 ;
typedef  enum m5mols_restype { ____Placeholder_m5mols_restype } m5mols_restype ;
struct TYPE_2__ {scalar_t__ code; } ;

/* Variables and functions */
 int M5MOLS_RESTYPE_MONITOR ; 
 scalar_t__ SIZE_DEFAULT_FFMT ; 
 TYPE_1__* m5mols_default_ffmt ; 

__attribute__((used)) static enum m5mols_restype __find_restype(u32 code)
{
	enum m5mols_restype type = M5MOLS_RESTYPE_MONITOR;

	do {
		if (code == m5mols_default_ffmt[type].code)
			return type;
	} while (type++ != SIZE_DEFAULT_FFMT);

	return 0;
}