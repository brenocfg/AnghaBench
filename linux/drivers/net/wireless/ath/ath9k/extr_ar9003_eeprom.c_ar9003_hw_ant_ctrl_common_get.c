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
struct ath_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  antCtrlCommon; } ;

/* Variables and functions */
 TYPE_1__* ar9003_modal_header (struct ath_hw*,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

u32 ar9003_hw_ant_ctrl_common_get(struct ath_hw *ah, bool is2ghz)
{
	return le32_to_cpu(ar9003_modal_header(ah, is2ghz)->antCtrlCommon);
}