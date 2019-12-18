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
typedef  int /*<<< orphan*/  xen_pfn_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct gnttab_get_status_frames {unsigned int nr_frames; scalar_t__ status; int /*<<< orphan*/  frame_list; int /*<<< orphan*/  dom; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DOMID_SELF ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GNTTABOP_get_status_frames ; 
 int HYPERVISOR_grant_table_op (int /*<<< orphan*/ ,struct gnttab_get_status_frames*,int) ; 
 int arch_gnttab_map_shared (int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int arch_gnttab_map_status (int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 unsigned int gnttab_max_grant_frames () ; 
 TYPE_1__ gnttab_shared ; 
 int /*<<< orphan*/  grstatus ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 unsigned int nr_status_frames (unsigned int) ; 
 int /*<<< orphan*/  set_xen_guest_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gnttab_map_frames_v2(xen_pfn_t *frames, unsigned int nr_gframes)
{
	uint64_t *sframes;
	unsigned int nr_sframes;
	struct gnttab_get_status_frames getframes;
	int rc;

	nr_sframes = nr_status_frames(nr_gframes);

	/* No need for kzalloc as it is initialized in following hypercall
	 * GNTTABOP_get_status_frames.
	 */
	sframes = kmalloc_array(nr_sframes, sizeof(uint64_t), GFP_ATOMIC);
	if (!sframes)
		return -ENOMEM;

	getframes.dom        = DOMID_SELF;
	getframes.nr_frames  = nr_sframes;
	set_xen_guest_handle(getframes.frame_list, sframes);

	rc = HYPERVISOR_grant_table_op(GNTTABOP_get_status_frames,
				       &getframes, 1);
	if (rc == -ENOSYS) {
		kfree(sframes);
		return -ENOSYS;
	}

	BUG_ON(rc || getframes.status);

	rc = arch_gnttab_map_status(sframes, nr_sframes,
				    nr_status_frames(gnttab_max_grant_frames()),
				    &grstatus);
	BUG_ON(rc);
	kfree(sframes);

	rc = arch_gnttab_map_shared(frames, nr_gframes,
				    gnttab_max_grant_frames(),
				    &gnttab_shared.addr);
	BUG_ON(rc);

	return 0;
}