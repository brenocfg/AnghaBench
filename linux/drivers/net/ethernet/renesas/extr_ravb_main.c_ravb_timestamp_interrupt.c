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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIS ; 
 int TIS_RESERVED ; 
 int TIS_TFUF ; 
 int /*<<< orphan*/  ravb_get_tx_tstamp (struct net_device*) ; 
 int ravb_read (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ravb_write (struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ravb_timestamp_interrupt(struct net_device *ndev)
{
	u32 tis = ravb_read(ndev, TIS);

	if (tis & TIS_TFUF) {
		ravb_write(ndev, ~(TIS_TFUF | TIS_RESERVED), TIS);
		ravb_get_tx_tstamp(ndev);
		return true;
	}
	return false;
}