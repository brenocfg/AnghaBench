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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct v4l2_standard {int index; scalar_t__* name; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_STD ; 
 struct v4l2_standard* match_std (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct v4l2_standard*,struct v4l2_standard*,int) ; 
 unsigned int pvr2_std_id_to_str (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,int,scalar_t__*) ; 

__attribute__((used)) static int pvr2_std_fill(struct v4l2_standard *std,v4l2_std_id id)
{
	struct v4l2_standard *template;
	int idx;
	unsigned int bcnt;
	template = match_std(id);
	if (!template) return 0;
	idx = std->index;
	memcpy(std,template,sizeof(*template));
	std->index = idx;
	std->id = id;
	bcnt = pvr2_std_id_to_str(std->name,sizeof(std->name)-1,id);
	std->name[bcnt] = 0;
	pvr2_trace(PVR2_TRACE_STD,"Set up standard idx=%u name=%s",
		   std->index,std->name);
	return !0;
}