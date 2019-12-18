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
typedef  int /*<<< orphan*/  u8 ;
struct iavf_mac_filter {int add; int remove; int /*<<< orphan*/  list; int /*<<< orphan*/  macaddr; } ;
struct iavf_adapter {int /*<<< orphan*/  aq_required; int /*<<< orphan*/  mac_filter_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IAVF_FLAG_AQ_ADD_MAC_FILTER ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 struct iavf_mac_filter* iavf_find_filter (struct iavf_adapter*,int /*<<< orphan*/  const*) ; 
 struct iavf_mac_filter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct
iavf_mac_filter *iavf_add_filter(struct iavf_adapter *adapter,
				 const u8 *macaddr)
{
	struct iavf_mac_filter *f;

	if (!macaddr)
		return NULL;

	f = iavf_find_filter(adapter, macaddr);
	if (!f) {
		f = kzalloc(sizeof(*f), GFP_ATOMIC);
		if (!f)
			return f;

		ether_addr_copy(f->macaddr, macaddr);

		list_add_tail(&f->list, &adapter->mac_filter_list);
		f->add = true;
		adapter->aq_required |= IAVF_FLAG_AQ_ADD_MAC_FILTER;
	} else {
		f->remove = false;
	}

	return f;
}