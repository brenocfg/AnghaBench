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
typedef  int u16 ;
struct net_local {scalar_t__ virt_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 

__attribute__((used)) static void writewords(struct net_local *lp, int portno, void *buf, int length)
{
	u8 *buf8 = (u8 *)buf;

	do {
		u16 tmp16;

		tmp16 = *buf8++;
		tmp16 |= (*buf8++) << 8;
		iowrite16(tmp16, lp->virt_addr + portno);
	} while (--length);
}