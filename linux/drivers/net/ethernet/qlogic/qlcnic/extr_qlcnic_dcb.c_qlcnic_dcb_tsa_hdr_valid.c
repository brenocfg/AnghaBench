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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLC_82XX_DCB_TSA_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_83XX_DCB_TSA_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 

__attribute__((used)) static inline u8 qlcnic_dcb_tsa_hdr_valid(struct qlcnic_adapter *adapter,
					  u32 val)
{
	if (qlcnic_82xx_check(adapter))
		return QLC_82XX_DCB_TSA_VALID(val);
	else
		return QLC_83XX_DCB_TSA_VALID(val);
}