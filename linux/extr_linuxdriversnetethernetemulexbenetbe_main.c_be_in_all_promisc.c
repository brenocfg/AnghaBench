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
struct be_adapter {int if_flags; } ;

/* Variables and functions */
 int BE_IF_FLAGS_ALL_PROMISCUOUS ; 

__attribute__((used)) static inline bool be_in_all_promisc(struct be_adapter *adapter)
{
	return (adapter->if_flags & BE_IF_FLAGS_ALL_PROMISCUOUS) ==
			BE_IF_FLAGS_ALL_PROMISCUOUS;
}