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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  mchip_fnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCHIP_MM_FIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mchip_read (int /*<<< orphan*/ ) ; 
 TYPE_1__ meye ; 

__attribute__((used)) static u32 mchip_get_frame(void)
{
	return mchip_read(MCHIP_MM_FIR(meye.mchip_fnum));
}