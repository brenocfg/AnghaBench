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
typedef  int /*<<< orphan*/  u32 ;
struct cqhci_host {scalar_t__ mmio; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_l ) (struct cqhci_host*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct cqhci_host*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/  (*) (struct cqhci_host*,int /*<<< orphan*/ ,int)) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void cqhci_writel(struct cqhci_host *host, u32 val, int reg)
{
	if (unlikely(host->ops->write_l))
		host->ops->write_l(host, val, reg);
	else
		writel_relaxed(val, host->mmio + reg);
}