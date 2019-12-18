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
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ bypass_mode; } ;
struct av7110 {TYPE_1__ audiostate; scalar_t__* pids; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMTYPE_PIDFILTER ; 
 size_t DMX_PES_AUDIO ; 
 size_t DMX_PES_PCR ; 
 size_t DMX_PES_TELETEXT ; 
 size_t DMX_PES_VIDEO ; 
 int /*<<< orphan*/  MultiPID ; 
 int av7110_fw_cmd (struct av7110*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 

__attribute__((used)) static inline int SetPIDs(struct av7110 *av7110, u16 vpid, u16 apid, u16 ttpid,
			  u16 subpid, u16 pcrpid)
{
	u16 aflags = 0;

	dprintk(4, "%p\n", av7110);

	if (vpid == 0x1fff || apid == 0x1fff ||
	    ttpid == 0x1fff || subpid == 0x1fff || pcrpid == 0x1fff) {
		vpid = apid = ttpid = subpid = pcrpid = 0;
		av7110->pids[DMX_PES_VIDEO] = 0;
		av7110->pids[DMX_PES_AUDIO] = 0;
		av7110->pids[DMX_PES_TELETEXT] = 0;
		av7110->pids[DMX_PES_PCR] = 0;
	}

	if (av7110->audiostate.bypass_mode)
		aflags |= 0x8000;

	return av7110_fw_cmd(av7110, COMTYPE_PIDFILTER, MultiPID, 6,
			     pcrpid, vpid, apid, ttpid, subpid, aflags);
}