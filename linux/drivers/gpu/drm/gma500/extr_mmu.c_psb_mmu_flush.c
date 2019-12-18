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
typedef  int uint32_t ;
struct psb_mmu_driver {int /*<<< orphan*/  sem; int /*<<< orphan*/ * msvdx_mmu_invaldc; int /*<<< orphan*/  needs_tlbflush; struct drm_device* dev; } ;
struct drm_psb_private {int dummy; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSB_CR_BIF_CTRL ; 
 int PSB_RSGX32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSB_WSGX32 (int,int /*<<< orphan*/ ) ; 
 int _PSB_CB_CTRL_FLUSH ; 
 int _PSB_CB_CTRL_INVALDC ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

void psb_mmu_flush(struct psb_mmu_driver *driver)
{
	struct drm_device *dev = driver->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	uint32_t val;

	down_write(&driver->sem);
	val = PSB_RSGX32(PSB_CR_BIF_CTRL);
	if (atomic_read(&driver->needs_tlbflush))
		PSB_WSGX32(val | _PSB_CB_CTRL_INVALDC, PSB_CR_BIF_CTRL);
	else
		PSB_WSGX32(val | _PSB_CB_CTRL_FLUSH, PSB_CR_BIF_CTRL);

	/* Make sure data cache is turned off and MMU is flushed before
	   restoring bank interface control register */
	wmb();
	PSB_WSGX32(val & ~(_PSB_CB_CTRL_FLUSH | _PSB_CB_CTRL_INVALDC),
		   PSB_CR_BIF_CTRL);
	(void)PSB_RSGX32(PSB_CR_BIF_CTRL);

	atomic_set(&driver->needs_tlbflush, 0);
	if (driver->msvdx_mmu_invaldc)
		atomic_set(driver->msvdx_mmu_invaldc, 1);
	up_write(&driver->sem);
}