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
typedef  unsigned int u8 ;
typedef  int u32 ;
struct _arg_GO {unsigned int chan; int addr; unsigned int ns; } ;

/* Variables and functions */
 unsigned int CMD_DMAGO ; 
 int SZ_DMAGO ; 

__attribute__((used)) static inline u32 _emit_GO(unsigned dry_run, u8 buf[],
		const struct _arg_GO *arg)
{
	u8 chan = arg->chan;
	u32 addr = arg->addr;
	unsigned ns = arg->ns;

	if (dry_run)
		return SZ_DMAGO;

	buf[0] = CMD_DMAGO;
	buf[0] |= (ns << 1);
	buf[1] = chan & 0x7;
	buf[2] = addr;
	buf[3] = addr >> 8;
	buf[4] = addr >> 16;
	buf[5] = addr >> 24;

	return SZ_DMAGO;
}