#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct TYPE_6__ {TYPE_1__* spurChans; } ;
struct TYPE_7__ {TYPE_2__ modalHeader; } ;
struct TYPE_8__ {TYPE_3__ map9287; } ;
struct ath_hw {TYPE_4__ eeprom; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_5__ {int /*<<< orphan*/  spurChan; } ;

/* Variables and functions */
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 ath9k_hw_ar9287_get_spur_channel(struct ath_hw *ah,
					    u16 i, bool is2GHz)
{
	__le16 spur_ch = ah->eeprom.map9287.modalHeader.spurChans[i].spurChan;

	return le16_to_cpu(spur_ch);
}