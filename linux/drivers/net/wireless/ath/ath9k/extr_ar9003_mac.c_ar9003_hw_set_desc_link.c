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
typedef  int /*<<< orphan*/  u32 ;
struct ar9003_txc {int /*<<< orphan*/  ctl10; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_TxPtrChkSum ; 
 int /*<<< orphan*/  ar9003_calc_ptr_chksum (struct ar9003_txc*) ; 

__attribute__((used)) static void ar9003_hw_set_desc_link(void *ds, u32 ds_link)
{
	struct ar9003_txc *ads = ds;

	ads->link = ds_link;
	ads->ctl10 &= ~AR_TxPtrChkSum;
	ads->ctl10 |= ar9003_calc_ptr_chksum(ads);
}