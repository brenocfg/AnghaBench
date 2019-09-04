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
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 

__attribute__((used)) static int cxgb4_setnumtcs(struct net_device *dev, int tcs_id, u8 num)
{
	/* Setting the number of Traffic Classes isn't supported.
	 */
	return -ENOSYS;
}