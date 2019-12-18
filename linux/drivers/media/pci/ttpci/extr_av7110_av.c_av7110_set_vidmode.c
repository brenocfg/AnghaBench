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
struct av7110 {int /*<<< orphan*/ * pids; int /*<<< orphan*/  playing; } ;
typedef  enum av7110_video_mode { ____Placeholder_av7110_video_mode } av7110_video_mode ;

/* Variables and functions */
 int /*<<< orphan*/  COMTYPE_ENCODER ; 
 int /*<<< orphan*/  COMTYPE_PIDFILTER ; 
 int ChangePIDs (struct av7110*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t DMX_PES_AUDIO ; 
 size_t DMX_PES_PCR ; 
 size_t DMX_PES_TELETEXT ; 
 size_t DMX_PES_VIDEO ; 
 int /*<<< orphan*/  LoadVidCode ; 
 int /*<<< orphan*/  Scan ; 
 int av7110_fw_cmd (struct av7110*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 

int av7110_set_vidmode(struct av7110 *av7110, enum av7110_video_mode mode)
{
	int ret;
	dprintk(2, "av7110:%p, \n", av7110);

	ret = av7110_fw_cmd(av7110, COMTYPE_ENCODER, LoadVidCode, 1, mode);

	if (!ret && !av7110->playing) {
		ret = ChangePIDs(av7110, av7110->pids[DMX_PES_VIDEO],
			   av7110->pids[DMX_PES_AUDIO],
			   av7110->pids[DMX_PES_TELETEXT],
			   0, av7110->pids[DMX_PES_PCR]);
		if (!ret)
			ret = av7110_fw_cmd(av7110, COMTYPE_PIDFILTER, Scan, 0);
	}
	return ret;
}