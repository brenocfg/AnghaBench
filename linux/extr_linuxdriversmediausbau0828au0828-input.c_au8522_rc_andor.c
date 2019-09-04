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
typedef  char u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct au0828_rc {int dummy; } ;

/* Variables and functions */
 int au8522_rc_read (struct au0828_rc*,int /*<<< orphan*/ ,int,char*,int) ; 
 int au8522_rc_write (struct au0828_rc*,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int au8522_rc_andor(struct au0828_rc *ir, u16 reg, u8 mask, u8 value)
{
	int rc;
	char buf, oldbuf;

	rc = au8522_rc_read(ir, reg, -1, &buf, 1);
	if (rc < 0)
		return rc;

	oldbuf = buf;
	buf = (buf & ~mask) | (value & mask);

	/* Nothing to do, just return */
	if (buf == oldbuf)
		return 0;

	return au8522_rc_write(ir, reg, buf);
}