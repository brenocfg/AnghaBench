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
typedef  int u32 ;
struct qlcnic_adapter {int portnum; int /*<<< orphan*/  ahw; } ;

/* Variables and functions */
 int QLCRDX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLCWRX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int QLC_83XX_IDC_MINOR_VERSION ; 
 int /*<<< orphan*/  QLC_83XX_IDC_MIN_VERSION ; 

__attribute__((used)) static void qlcnic_83xx_idc_update_minor_version(struct qlcnic_adapter *adapter)
{
	u32 val;

	val = QLCRDX(adapter->ahw, QLC_83XX_IDC_MIN_VERSION);
	val = val & ~(0x3 << (adapter->portnum * 2));
	val = val | (QLC_83XX_IDC_MINOR_VERSION << (adapter->portnum * 2));
	QLCWRX(adapter->ahw, QLC_83XX_IDC_MIN_VERSION, val);
}