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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  streamId; int /*<<< orphan*/  cmdType; } ;
struct vmw_escape_video_flush {TYPE_1__ flush; int /*<<< orphan*/  escape; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVGA_ESCAPE_VMWARE_VIDEO_FLUSH ; 
 int /*<<< orphan*/  fill_escape (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void fill_flush(struct vmw_escape_video_flush *cmd,
			      uint32_t stream_id)
{
	fill_escape(&cmd->escape, sizeof(cmd->flush));
	cmd->flush.cmdType = SVGA_ESCAPE_VMWARE_VIDEO_FLUSH;
	cmd->flush.streamId = stream_id;
}