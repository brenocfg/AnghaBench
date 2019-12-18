#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  tbuf ;
struct pvr2_hdw {int* cmd_buffer; int /*<<< orphan*/  ctl_lock; } ;
struct TYPE_3__ {int id; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 int PVR2_TRACE_INIT ; 
 TYPE_1__* pvr2_fx2cmd_desc ; 
 int pvr2_send_request (struct pvr2_hdw*,int*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_trace (int,char*,unsigned int,char*) ; 
 int pvrusb2_debug ; 
 unsigned int scnprintf (char*,int,char*,...) ; 

__attribute__((used)) static int pvr2_issue_simple_cmd(struct pvr2_hdw *hdw,u32 cmdcode)
{
	int ret;
	unsigned int cnt = 1;
	unsigned int args = 0;
	LOCK_TAKE(hdw->ctl_lock);
	hdw->cmd_buffer[0] = cmdcode & 0xffu;
	args = (cmdcode >> 8) & 0xffu;
	args = (args > 2) ? 2 : args;
	if (args) {
		cnt += args;
		hdw->cmd_buffer[1] = (cmdcode >> 16) & 0xffu;
		if (args > 1) {
			hdw->cmd_buffer[2] = (cmdcode >> 24) & 0xffu;
		}
	}
	if (pvrusb2_debug & PVR2_TRACE_INIT) {
		unsigned int idx;
		unsigned int ccnt,bcnt;
		char tbuf[50];
		cmdcode &= 0xffu;
		bcnt = 0;
		ccnt = scnprintf(tbuf+bcnt,
				 sizeof(tbuf)-bcnt,
				 "Sending FX2 command 0x%x",cmdcode);
		bcnt += ccnt;
		for (idx = 0; idx < ARRAY_SIZE(pvr2_fx2cmd_desc); idx++) {
			if (pvr2_fx2cmd_desc[idx].id == cmdcode) {
				ccnt = scnprintf(tbuf+bcnt,
						 sizeof(tbuf)-bcnt,
						 " \"%s\"",
						 pvr2_fx2cmd_desc[idx].desc);
				bcnt += ccnt;
				break;
			}
		}
		if (args) {
			ccnt = scnprintf(tbuf+bcnt,
					 sizeof(tbuf)-bcnt,
					 " (%u",hdw->cmd_buffer[1]);
			bcnt += ccnt;
			if (args > 1) {
				ccnt = scnprintf(tbuf+bcnt,
						 sizeof(tbuf)-bcnt,
						 ",%u",hdw->cmd_buffer[2]);
				bcnt += ccnt;
			}
			ccnt = scnprintf(tbuf+bcnt,
					 sizeof(tbuf)-bcnt,
					 ")");
			bcnt += ccnt;
		}
		pvr2_trace(PVR2_TRACE_INIT,"%.*s",bcnt,tbuf);
	}
	ret = pvr2_send_request(hdw,hdw->cmd_buffer,cnt,NULL,0);
	LOCK_GIVE(hdw->ctl_lock);
	return ret;
}