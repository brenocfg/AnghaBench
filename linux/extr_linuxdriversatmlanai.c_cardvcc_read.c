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
struct lanai_vcc {int /*<<< orphan*/  vci; int /*<<< orphan*/ * vbase; } ;
typedef  enum lanai_vcc_offset { ____Placeholder_lanai_vcc_offset } lanai_vcc_offset ;

/* Variables and functions */
 int /*<<< orphan*/  APRINTK (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RWDEBUG (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 cardvcc_read(const struct lanai_vcc *lvcc,
	enum lanai_vcc_offset offset)
{
	u32 val;
	APRINTK(lvcc->vbase != NULL, "cardvcc_read: unbound vcc!\n");
	val= readl(lvcc->vbase + offset);
	RWDEBUG("VR vci=%04d 0x%02X = 0x%08X\n",
	    lvcc->vci, (int) offset, val);
	return val;
}