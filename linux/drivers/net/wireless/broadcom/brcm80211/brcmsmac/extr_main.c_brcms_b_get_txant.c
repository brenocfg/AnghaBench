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
typedef  int /*<<< orphan*/  u16 ;
struct brcms_hardware {TYPE_2__* wlc; } ;
struct TYPE_4__ {TYPE_1__* stf; } ;
struct TYPE_3__ {int /*<<< orphan*/  txant; } ;

/* Variables and functions */

u16 brcms_b_get_txant(struct brcms_hardware *wlc_hw)
{
	return (u16) wlc_hw->wlc->stf->txant;
}