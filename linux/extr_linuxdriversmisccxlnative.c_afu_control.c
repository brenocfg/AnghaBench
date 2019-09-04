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
typedef  int u64 ;
struct cxl_afu {int enabled; int /*<<< orphan*/  afu_cntl_lock; int /*<<< orphan*/  adapter; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* link_ok ) (int /*<<< orphan*/ ,struct cxl_afu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_AFU_Cntl_An ; 
 int CXL_AFU_Cntl_An_RA ; 
 unsigned long CXL_TIMEOUT ; 
 int EBUSY ; 
 int EIO ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_1__* cxl_ops ; 
 int cxl_p2n_read (struct cxl_afu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_p2n_write (struct cxl_afu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  pr_devel (char*,int) ; 
 int /*<<< orphan*/  pr_devel_ratelimited (char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct cxl_afu*) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  trace_cxl_afu_ctrl (struct cxl_afu*,int) ; 
 int /*<<< orphan*/  trace_cxl_afu_ctrl_done (struct cxl_afu*,int,int) ; 

__attribute__((used)) static int afu_control(struct cxl_afu *afu, u64 command, u64 clear,
		       u64 result, u64 mask, bool enabled)
{
	u64 AFU_Cntl;
	unsigned long timeout = jiffies + (HZ * CXL_TIMEOUT);
	int rc = 0;

	spin_lock(&afu->afu_cntl_lock);
	pr_devel("AFU command starting: %llx\n", command);

	trace_cxl_afu_ctrl(afu, command);

	AFU_Cntl = cxl_p2n_read(afu, CXL_AFU_Cntl_An);
	cxl_p2n_write(afu, CXL_AFU_Cntl_An, (AFU_Cntl & ~clear) | command);

	AFU_Cntl = cxl_p2n_read(afu, CXL_AFU_Cntl_An);
	while ((AFU_Cntl & mask) != result) {
		if (time_after_eq(jiffies, timeout)) {
			dev_warn(&afu->dev, "WARNING: AFU control timed out!\n");
			rc = -EBUSY;
			goto out;
		}

		if (!cxl_ops->link_ok(afu->adapter, afu)) {
			afu->enabled = enabled;
			rc = -EIO;
			goto out;
		}

		pr_devel_ratelimited("AFU control... (0x%016llx)\n",
				     AFU_Cntl | command);
		cpu_relax();
		AFU_Cntl = cxl_p2n_read(afu, CXL_AFU_Cntl_An);
	}

	if (AFU_Cntl & CXL_AFU_Cntl_An_RA) {
		/*
		 * Workaround for a bug in the XSL used in the Mellanox CX4
		 * that fails to clear the RA bit after an AFU reset,
		 * preventing subsequent AFU resets from working.
		 */
		cxl_p2n_write(afu, CXL_AFU_Cntl_An, AFU_Cntl & ~CXL_AFU_Cntl_An_RA);
	}

	pr_devel("AFU command complete: %llx\n", command);
	afu->enabled = enabled;
out:
	trace_cxl_afu_ctrl_done(afu, command, rc);
	spin_unlock(&afu->afu_cntl_lock);

	return rc;
}