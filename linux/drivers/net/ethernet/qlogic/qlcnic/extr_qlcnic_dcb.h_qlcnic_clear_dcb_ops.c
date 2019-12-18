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
struct qlcnic_dcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct qlcnic_dcb*) ; 

__attribute__((used)) static inline void qlcnic_clear_dcb_ops(struct qlcnic_dcb *dcb)
{
	kfree(dcb);
}