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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  set_tx_desc_first_seg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_last_seg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_own (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void _rtl_fill_usb_tx_desc(__le32 *txdesc)
{
	set_tx_desc_own(txdesc, 1);
	set_tx_desc_last_seg(txdesc, 1);
	set_tx_desc_first_seg(txdesc, 1);
}