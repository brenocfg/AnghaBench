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
typedef  int /*<<< orphan*/  u16 ;
struct isp1362_hcd {int /*<<< orphan*/  data_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMMY_DELAY_ACCESS ; 
 int /*<<< orphan*/  readw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 isp1362_read_data16(struct isp1362_hcd *isp1362_hcd)
{
	u16 val;

	DUMMY_DELAY_ACCESS;
	val = readw(isp1362_hcd->data_reg);

	return val;
}