#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct brcms_c_info {TYPE_2__** bandstate; TYPE_1__* stf; } ;
typedef  void* s8 ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {void* band_stf_stbc_tx; } ;
struct TYPE_3__ {int txstreams; } ;

/* Variables and functions */
 scalar_t__ AUTO ; 
 size_t BAND_2G_INDEX ; 
 size_t BAND_5G_INDEX ; 
 scalar_t__ OFF ; 
 scalar_t__ ON ; 

__attribute__((used)) static bool brcms_c_stf_stbc_tx_set(struct brcms_c_info *wlc, s32 int_val)
{
	if ((int_val != AUTO) && (int_val != OFF) && (int_val != ON))
		return false;

	if ((int_val == ON) && (wlc->stf->txstreams == 1))
		return false;

	wlc->bandstate[BAND_2G_INDEX]->band_stf_stbc_tx = (s8) int_val;
	wlc->bandstate[BAND_5G_INDEX]->band_stf_stbc_tx = (s8) int_val;

	return true;
}