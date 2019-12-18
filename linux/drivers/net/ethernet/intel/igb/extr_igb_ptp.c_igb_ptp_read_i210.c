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
typedef  void* u32 ;
struct timespec64 {void* tv_nsec; void* tv_sec; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_SYSTIMH ; 
 int /*<<< orphan*/  E1000_SYSTIML ; 
 int /*<<< orphan*/  E1000_SYSTIMR ; 
 void* rd32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igb_ptp_read_i210(struct igb_adapter *adapter,
			      struct timespec64 *ts)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 sec, nsec;

	/* The timestamp latches on lowest register read. For I210/I211, the
	 * lowest register is SYSTIMR. Since we only need to provide nanosecond
	 * resolution, we can ignore it.
	 */
	rd32(E1000_SYSTIMR);
	nsec = rd32(E1000_SYSTIML);
	sec = rd32(E1000_SYSTIMH);

	ts->tv_sec = sec;
	ts->tv_nsec = nsec;
}