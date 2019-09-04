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
struct idr {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SWID_END ; 
 int /*<<< orphan*/  SWID_START ; 
 int idr_alloc (struct idr*,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mlx5_fpga_tls_alloc_swid(struct idr *idr, spinlock_t *idr_spinlock,
				    void *ptr)
{
	unsigned long flags;
	int ret;

	/* TLS metadata format is 1 byte for syndrome followed
	 * by 3 bytes of swid (software ID)
	 * swid must not exceed 3 bytes.
	 * See tls_rxtx.c:insert_pet() for details
	 */
	BUILD_BUG_ON((SWID_END - 1) & 0xFF000000);

	idr_preload(GFP_KERNEL);
	spin_lock_irqsave(idr_spinlock, flags);
	ret = idr_alloc(idr, ptr, SWID_START, SWID_END, GFP_ATOMIC);
	spin_unlock_irqrestore(idr_spinlock, flags);
	idr_preload_end();

	return ret;
}