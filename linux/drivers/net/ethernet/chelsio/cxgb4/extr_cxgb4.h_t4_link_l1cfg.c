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
struct link_config {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_CMD_MAX_TIMEOUT ; 
 int t4_link_l1cfg_core (struct adapter*,unsigned int,unsigned int,struct link_config*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int t4_link_l1cfg(struct adapter *adapter, unsigned int mbox,
				unsigned int port, struct link_config *lc)
{
	return t4_link_l1cfg_core(adapter, mbox, port, lc,
				  true, FW_CMD_MAX_TIMEOUT);
}