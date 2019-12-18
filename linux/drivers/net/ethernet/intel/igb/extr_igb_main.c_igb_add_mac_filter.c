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
struct igb_adapter {int dummy; } ;

/* Variables and functions */
 int igb_add_mac_filter_flags (struct igb_adapter*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int igb_add_mac_filter(struct igb_adapter *adapter, const u8 *addr,
			      const u8 queue)
{
	return igb_add_mac_filter_flags(adapter, addr, queue, 0);
}