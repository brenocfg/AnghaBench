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
typedef  int uint64_t ;
typedef  size_t uint32_t ;
typedef  int uint16_t ;
struct amdgpu_gmc_fault {int timestamp; int key; size_t next; } ;
struct amdgpu_gmc {size_t last_fault; TYPE_1__* fault_hash; struct amdgpu_gmc_fault* fault_ring; } ;
struct amdgpu_device {struct amdgpu_gmc gmc; } ;
struct TYPE_2__ {size_t idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GMC_FAULT_HASH_ORDER ; 
 int AMDGPU_GMC_FAULT_TIMEOUT ; 
 size_t hash_64 (int,int /*<<< orphan*/ ) ; 
 int max (int,int) ; 

bool amdgpu_gmc_filter_faults(struct amdgpu_device *adev, uint64_t addr,
			      uint16_t pasid, uint64_t timestamp)
{
	struct amdgpu_gmc *gmc = &adev->gmc;

	uint64_t stamp, key = addr << 4 | pasid;
	struct amdgpu_gmc_fault *fault;
	uint32_t hash;

	/* If we don't have space left in the ring buffer return immediately */
	stamp = max(timestamp, AMDGPU_GMC_FAULT_TIMEOUT + 1) -
		AMDGPU_GMC_FAULT_TIMEOUT;
	if (gmc->fault_ring[gmc->last_fault].timestamp >= stamp)
		return true;

	/* Try to find the fault in the hash */
	hash = hash_64(key, AMDGPU_GMC_FAULT_HASH_ORDER);
	fault = &gmc->fault_ring[gmc->fault_hash[hash].idx];
	while (fault->timestamp >= stamp) {
		uint64_t tmp;

		if (fault->key == key)
			return true;

		tmp = fault->timestamp;
		fault = &gmc->fault_ring[fault->next];

		/* Check if the entry was reused */
		if (fault->timestamp >= tmp)
			break;
	}

	/* Add the fault to the ring */
	fault = &gmc->fault_ring[gmc->last_fault];
	fault->key = key;
	fault->timestamp = timestamp;

	/* And update the hash */
	fault->next = gmc->fault_hash[hash].idx;
	gmc->fault_hash[hash].idx = gmc->last_fault++;
	return false;
}