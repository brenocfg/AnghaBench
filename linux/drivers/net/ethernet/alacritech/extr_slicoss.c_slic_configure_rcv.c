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
struct slic_device {scalar_t__ duplex; scalar_t__ promisc; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int SLIC_GRCR_ADDRAEN ; 
 int SLIC_GRCR_CTLEN ; 
 int SLIC_GRCR_HASHSIZE ; 
 int SLIC_GRCR_HASHSIZE_SHIFT ; 
 int SLIC_GRCR_RCVALL ; 
 int SLIC_GRCR_RCVBAD ; 
 int SLIC_GRCR_RCVEN ; 
 int SLIC_GRCR_RESET ; 
 int /*<<< orphan*/  SLIC_REG_WRCFG ; 
 int /*<<< orphan*/  slic_write (struct slic_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void slic_configure_rcv(struct slic_device *sdev)
{
	u32 val;

	val = SLIC_GRCR_RESET | SLIC_GRCR_ADDRAEN | SLIC_GRCR_RCVEN |
	      SLIC_GRCR_HASHSIZE << SLIC_GRCR_HASHSIZE_SHIFT | SLIC_GRCR_RCVBAD;

	if (sdev->duplex == DUPLEX_FULL)
		val |= SLIC_GRCR_CTLEN;

	if (sdev->promisc)
		val |= SLIC_GRCR_RCVALL;

	slic_write(sdev, SLIC_REG_WRCFG, val);
}