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
typedef  size_t u32 ;
struct octeon_device {size_t octeon_id; int /*<<< orphan*/  device_name; int /*<<< orphan*/  mem_access_lock; int /*<<< orphan*/  pci_win_lock; } ;

/* Variables and functions */
 size_t MAX_OCTEON_DEVICES ; 
 struct octeon_device* octeon_allocate_device_mem (size_t,size_t) ; 
 struct octeon_device** octeon_device ; 
 int /*<<< orphan*/  octeon_device_count ; 
 int /*<<< orphan*/  octeon_devices_lock ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct octeon_device *octeon_allocate_device(u32 pci_id,
					     u32 priv_size)
{
	u32 oct_idx = 0;
	struct octeon_device *oct = NULL;

	spin_lock(&octeon_devices_lock);

	for (oct_idx = 0; oct_idx < MAX_OCTEON_DEVICES; oct_idx++)
		if (!octeon_device[oct_idx])
			break;

	if (oct_idx < MAX_OCTEON_DEVICES) {
		oct = octeon_allocate_device_mem(pci_id, priv_size);
		if (oct) {
			octeon_device_count++;
			octeon_device[oct_idx] = oct;
		}
	}

	spin_unlock(&octeon_devices_lock);
	if (!oct)
		return NULL;

	spin_lock_init(&oct->pci_win_lock);
	spin_lock_init(&oct->mem_access_lock);

	oct->octeon_id = oct_idx;
	snprintf(oct->device_name, sizeof(oct->device_name),
		 "LiquidIO%d", (oct->octeon_id));

	return oct;
}