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
typedef  int u16 ;
struct av7110 {int* pids; int /*<<< orphan*/  pid_mutex; scalar_t__ fe_synced; } ;

/* Variables and functions */
 size_t DMX_PES_AUDIO ; 
 size_t DMX_PES_PCR ; 
 size_t DMX_PES_SUBTITLE ; 
 size_t DMX_PES_TELETEXT ; 
 size_t DMX_PES_VIDEO ; 
 int ERESTARTSYS ; 
 int SetPIDs (struct av7110*,int,int,int,int,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ChangePIDs(struct av7110 *av7110, u16 vpid, u16 apid, u16 ttpid,
		u16 subpid, u16 pcrpid)
{
	int ret = 0;
	dprintk(4, "%p\n", av7110);

	if (mutex_lock_interruptible(&av7110->pid_mutex))
		return -ERESTARTSYS;

	if (!(vpid & 0x8000))
		av7110->pids[DMX_PES_VIDEO] = vpid;
	if (!(apid & 0x8000))
		av7110->pids[DMX_PES_AUDIO] = apid;
	if (!(ttpid & 0x8000))
		av7110->pids[DMX_PES_TELETEXT] = ttpid;
	if (!(pcrpid & 0x8000))
		av7110->pids[DMX_PES_PCR] = pcrpid;

	av7110->pids[DMX_PES_SUBTITLE] = 0;

	if (av7110->fe_synced) {
		pcrpid = av7110->pids[DMX_PES_PCR];
		ret = SetPIDs(av7110, vpid, apid, ttpid, subpid, pcrpid);
	}

	mutex_unlock(&av7110->pid_mutex);
	return ret;
}