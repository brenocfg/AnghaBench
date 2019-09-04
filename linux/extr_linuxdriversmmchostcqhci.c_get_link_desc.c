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
struct cqhci_host {int task_desc_len; } ;

/* Variables and functions */
 int /*<<< orphan*/ * get_desc (struct cqhci_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 *get_link_desc(struct cqhci_host *cq_host, u8 tag)
{
	u8 *desc = get_desc(cq_host, tag);

	return desc + cq_host->task_desc_len;
}