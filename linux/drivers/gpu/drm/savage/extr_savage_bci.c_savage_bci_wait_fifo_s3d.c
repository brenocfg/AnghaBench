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
typedef  int uint32_t ;
struct TYPE_3__ {int cob_size; } ;
typedef  TYPE_1__ drm_savage_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int) ; 
 int EBUSY ; 
 int SAVAGE_BCI_FIFO_SIZE ; 
 int SAVAGE_DEFAULT_USEC_TIMEOUT ; 
 int SAVAGE_FIFO_USED_MASK_S3D ; 
 int SAVAGE_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAVAGE_STATUS_WORD0 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
savage_bci_wait_fifo_s3d(drm_savage_private_t * dev_priv, unsigned int n)
{
	uint32_t maxUsed = dev_priv->cob_size + SAVAGE_BCI_FIFO_SIZE - n;
	uint32_t status;
	int i;

	for (i = 0; i < SAVAGE_DEFAULT_USEC_TIMEOUT; i++) {
		status = SAVAGE_READ(SAVAGE_STATUS_WORD0);
		if ((status & SAVAGE_FIFO_USED_MASK_S3D) <= maxUsed)
			return 0;
		udelay(1);
	}

#if SAVAGE_BCI_DEBUG
	DRM_ERROR("failed!\n");
	DRM_INFO("   status=0x%08x\n", status);
#endif
	return -EBUSY;
}