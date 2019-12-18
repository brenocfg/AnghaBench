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
struct hisi_femac_mdio_data {scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ MDIO_RWCTRL ; 
 int MDIO_RW_FINISH ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static int hisi_femac_mdio_wait_ready(struct hisi_femac_mdio_data *data)
{
	u32 val;

	return readl_poll_timeout(data->membase + MDIO_RWCTRL,
				  val, val & MDIO_RW_FINISH, 20, 10000);
}