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
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 

__attribute__((used)) static int dummy_rx_push_rss_config(struct ef4_nic *efx, bool user,
				    const u32 *rx_indir_table)
{
	(void) efx;
	(void) user;
	(void) rx_indir_table;
	return -ENOSYS;
}