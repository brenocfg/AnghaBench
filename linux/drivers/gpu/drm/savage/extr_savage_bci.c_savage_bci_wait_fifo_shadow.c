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
struct TYPE_3__ {int status_used_mask; int bci_threshold_hi; unsigned int cob_size; int* status_ptr; } ;
typedef  TYPE_1__ drm_savage_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int,int) ; 
 int EBUSY ; 
 unsigned int SAVAGE_BCI_FIFO_SIZE ; 
 int SAVAGE_DEFAULT_USEC_TIMEOUT ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
savage_bci_wait_fifo_shadow(drm_savage_private_t * dev_priv, unsigned int n)
{
	uint32_t mask = dev_priv->status_used_mask;
	uint32_t threshold = dev_priv->bci_threshold_hi;
	uint32_t status;
	int i;

#if SAVAGE_BCI_DEBUG
	if (n > dev_priv->cob_size + SAVAGE_BCI_FIFO_SIZE - threshold)
		DRM_ERROR("Trying to emit %d words "
			  "(more than guaranteed space in COB)\n", n);
#endif

	for (i = 0; i < SAVAGE_DEFAULT_USEC_TIMEOUT; i++) {
		mb();
		status = dev_priv->status_ptr[0];
		if ((status & mask) < threshold)
			return 0;
		udelay(1);
	}

#if SAVAGE_BCI_DEBUG
	DRM_ERROR("failed!\n");
	DRM_INFO("   status=0x%08x, threshold=0x%08x\n", status, threshold);
#endif
	return -EBUSY;
}