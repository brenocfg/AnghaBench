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
typedef  void u8 ;
struct e1000_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_HEADROOM ; 
 unsigned int e1000_frag_len (struct e1000_adapter const*) ; 
 scalar_t__ likely (void*) ; 
 void* netdev_alloc_frag (unsigned int) ; 

__attribute__((used)) static void *e1000_alloc_frag(const struct e1000_adapter *a)
{
	unsigned int len = e1000_frag_len(a);
	u8 *data = netdev_alloc_frag(len);

	if (likely(data))
		data += E1000_HEADROOM;
	return data;
}