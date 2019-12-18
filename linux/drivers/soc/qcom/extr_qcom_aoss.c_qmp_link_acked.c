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
struct qmp {scalar_t__ msgram; } ;

/* Variables and functions */
 scalar_t__ QMP_DESC_MCORE_LINK_STATE_ACK ; 
 scalar_t__ QMP_STATE_UP ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static bool qmp_link_acked(struct qmp *qmp)
{
	return readl(qmp->msgram + QMP_DESC_MCORE_LINK_STATE_ACK) == QMP_STATE_UP;
}