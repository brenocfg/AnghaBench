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
struct lanai_vcc {int /*<<< orphan*/ * vbase; int /*<<< orphan*/  vci; } ;
typedef  enum lanai_vcc_offset { ____Placeholder_lanai_vcc_offset } lanai_vcc_offset ;

/* Variables and functions */
 int /*<<< orphan*/  APRINTK (int,char*,...) ; 
 int /*<<< orphan*/  RWDEBUG (char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cardvcc_write(const struct lanai_vcc *lvcc,
	u32 val, enum lanai_vcc_offset offset)
{
	APRINTK(lvcc->vbase != NULL, "cardvcc_write: unbound vcc!\n");
	APRINTK((val & ~0xFFFF) == 0,
	    "cardvcc_write: bad val 0x%X (vci=%d, addr=0x%02X)\n",
	    (unsigned int) val, lvcc->vci, (unsigned int) offset);
	RWDEBUG("VW vci=%04d 0x%02X > 0x%08X\n",
	    lvcc->vci, (unsigned int) offset, (unsigned int) val);
	writel(val, lvcc->vbase + offset);
}