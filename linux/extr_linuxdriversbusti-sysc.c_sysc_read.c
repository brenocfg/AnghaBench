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
typedef  int u32 ;
struct TYPE_2__ {int quirks; } ;
struct sysc {scalar_t__ module_va; TYPE_1__ cfg; } ;

/* Variables and functions */
 int SYSC_QUIRK_16BIT ; 
 int readl_relaxed (scalar_t__) ; 
 int readw_relaxed (scalar_t__) ; 

__attribute__((used)) static u32 sysc_read(struct sysc *ddata, int offset)
{
	if (ddata->cfg.quirks & SYSC_QUIRK_16BIT) {
		u32 val;

		val = readw_relaxed(ddata->module_va + offset);
		val |= (readw_relaxed(ddata->module_va + offset + 4) << 16);

		return val;
	}

	return readl_relaxed(ddata->module_va + offset);
}