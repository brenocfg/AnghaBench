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
struct TYPE_2__ {int atc; int /*<<< orphan*/  mask; scalar_t__ valid; } ;
union TCP_WATCH_CNTL_BITS {scalar_t__ u32All; TYPE_1__ bitfields; } ;
struct kgd_dev {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 unsigned int ADDRESS_WATCH_REG_CNTL ; 
 int /*<<< orphan*/  ADDRESS_WATCH_REG_CNTL_DEFAULT_MASK ; 
 unsigned int ADDRESS_WATCH_REG_MAX ; 
 unsigned int MAX_WATCH_ADDRESSES ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 int /*<<< orphan*/ * watchRegs ; 

__attribute__((used)) static int kgd_address_watch_disable(struct kgd_dev *kgd)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);
	union TCP_WATCH_CNTL_BITS cntl;
	unsigned int i;

	cntl.u32All = 0;

	cntl.bitfields.valid = 0;
	cntl.bitfields.mask = ADDRESS_WATCH_REG_CNTL_DEFAULT_MASK;
	cntl.bitfields.atc = 1;

	/* Turning off this address until we set all the registers */
	for (i = 0; i < MAX_WATCH_ADDRESSES; i++)
		WREG32(watchRegs[i * ADDRESS_WATCH_REG_MAX +
			ADDRESS_WATCH_REG_CNTL], cntl.u32All);

	return 0;
}