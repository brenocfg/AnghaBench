#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int buf_sz; } ;
struct velocity_info {TYPE_1__ rx; } ;

/* Variables and functions */
 int ETH_DATA_LEN ; 
 int PKT_BUF_SZ ; 

__attribute__((used)) static void velocity_set_rxbufsize(struct velocity_info *vptr, int mtu)
{
	vptr->rx.buf_sz = (mtu <= ETH_DATA_LEN) ? PKT_BUF_SZ : mtu + 32;
}