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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u16 ;
struct ksz_device {int dummy; } ;
struct TYPE_2__ {size_t index; } ;

/* Variables and functions */
 TYPE_1__* ksz9477_mib_names ; 
 int /*<<< orphan*/  ksz9477_r_mib_cnt (struct ksz_device*,int,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ksz9477_r_mib_pkt(struct ksz_device *dev, int port, u16 addr,
			      u64 *dropped, u64 *cnt)
{
	addr = ksz9477_mib_names[addr].index;
	ksz9477_r_mib_cnt(dev, port, addr, cnt);
}