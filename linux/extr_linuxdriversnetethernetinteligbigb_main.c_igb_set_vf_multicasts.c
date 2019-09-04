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
typedef  int /*<<< orphan*/  u16 ;
struct vf_data_storage {int num_vf_mc_hashes; int /*<<< orphan*/ * vf_mc_hashes; } ;
struct igb_adapter {int /*<<< orphan*/  netdev; struct vf_data_storage* vf_data; } ;

/* Variables and functions */
 size_t E1000_VT_MSGINFO_MASK ; 
 size_t E1000_VT_MSGINFO_SHIFT ; 
 int /*<<< orphan*/  igb_set_rx_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int igb_set_vf_multicasts(struct igb_adapter *adapter,
				  u32 *msgbuf, u32 vf)
{
	int n = (msgbuf[0] & E1000_VT_MSGINFO_MASK) >> E1000_VT_MSGINFO_SHIFT;
	u16 *hash_list = (u16 *)&msgbuf[1];
	struct vf_data_storage *vf_data = &adapter->vf_data[vf];
	int i;

	/* salt away the number of multicast addresses assigned
	 * to this VF for later use to restore when the PF multi cast
	 * list changes
	 */
	vf_data->num_vf_mc_hashes = n;

	/* only up to 30 hash values supported */
	if (n > 30)
		n = 30;

	/* store the hashes for later use */
	for (i = 0; i < n; i++)
		vf_data->vf_mc_hashes[i] = hash_list[i];

	/* Flush and reset the mta with the new values */
	igb_set_rx_mode(adapter->netdev);

	return 0;
}