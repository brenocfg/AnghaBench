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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMWIN_NIC ; 
 int /*<<< orphan*/  t4_get_util_window (struct adapter*) ; 
 int /*<<< orphan*/  t4_setup_memwin (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_memwin(struct adapter *adap)
{
	u32 nic_win_base = t4_get_util_window(adap);

	t4_setup_memwin(adap, nic_win_base, MEMWIN_NIC);
}