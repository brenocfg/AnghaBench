#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long dwFrames; TYPE_1__* frame; } ;
struct s2255_vc {int last_frame; scalar_t__ cur_frame; TYPE_2__ buffer; } ;
struct TYPE_3__ {unsigned long size; scalar_t__ cur_size; scalar_t__ ulState; int /*<<< orphan*/ * lpvbits; } ;

/* Variables and functions */
 unsigned long SYS_FRAMES ; 
 unsigned long SYS_FRAMES_MAXSIZE ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/ * vmalloc (unsigned long) ; 

__attribute__((used)) static int s2255_create_sys_buffers(struct s2255_vc *vc)
{
	unsigned long i;
	unsigned long reqsize;
	vc->buffer.dwFrames = SYS_FRAMES;
	/* always allocate maximum size(PAL) for system buffers */
	reqsize = SYS_FRAMES_MAXSIZE;

	if (reqsize > SYS_FRAMES_MAXSIZE)
		reqsize = SYS_FRAMES_MAXSIZE;

	for (i = 0; i < SYS_FRAMES; i++) {
		/* allocate the frames */
		vc->buffer.frame[i].lpvbits = vmalloc(reqsize);
		vc->buffer.frame[i].size = reqsize;
		if (vc->buffer.frame[i].lpvbits == NULL) {
			pr_info("out of memory.  using less frames\n");
			vc->buffer.dwFrames = i;
			break;
		}
	}

	/* make sure internal states are set */
	for (i = 0; i < SYS_FRAMES; i++) {
		vc->buffer.frame[i].ulState = 0;
		vc->buffer.frame[i].cur_size = 0;
	}

	vc->cur_frame = 0;
	vc->last_frame = -1;
	return 0;
}