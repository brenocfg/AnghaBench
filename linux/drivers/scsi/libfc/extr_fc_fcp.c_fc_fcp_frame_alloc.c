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
struct fc_lport {TYPE_1__* host; int /*<<< orphan*/  stats; } ;
struct fc_frame {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  FcpFrameAllocFails; } ;
struct TYPE_3__ {int /*<<< orphan*/  can_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  fc_fcp_can_queue_ramp_down (struct fc_lport*) ; 
 struct fc_frame* fc_frame_alloc (struct fc_lport*,size_t) ; 
 int /*<<< orphan*/  get_cpu () ; 
 scalar_t__ likely (struct fc_frame*) ; 
 TYPE_2__* per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct fc_frame *fc_fcp_frame_alloc(struct fc_lport *lport,
						  size_t len)
{
	struct fc_frame *fp;

	fp = fc_frame_alloc(lport, len);
	if (likely(fp))
		return fp;

	per_cpu_ptr(lport->stats, get_cpu())->FcpFrameAllocFails++;
	put_cpu();
	/* error case */
	fc_fcp_can_queue_ramp_down(lport);
	shost_printk(KERN_ERR, lport->host,
		     "libfc: Could not allocate frame, "
		     "reducing can_queue to %d.\n", lport->host->can_queue);
	return NULL;
}