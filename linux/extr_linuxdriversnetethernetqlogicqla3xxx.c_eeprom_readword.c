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
struct ql3_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ FM93C56A_READ ; 
 int /*<<< orphan*/  fm93c56a_cmd (struct ql3_adapter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm93c56a_datain (struct ql3_adapter*,unsigned short*) ; 
 int /*<<< orphan*/  fm93c56a_deselect (struct ql3_adapter*) ; 
 int /*<<< orphan*/  fm93c56a_select (struct ql3_adapter*) ; 

__attribute__((used)) static void eeprom_readword(struct ql3_adapter *qdev,
			    u32 eepromAddr, unsigned short *value)
{
	fm93c56a_select(qdev);
	fm93c56a_cmd(qdev, (int)FM93C56A_READ, eepromAddr);
	fm93c56a_datain(qdev, value);
	fm93c56a_deselect(qdev);
}