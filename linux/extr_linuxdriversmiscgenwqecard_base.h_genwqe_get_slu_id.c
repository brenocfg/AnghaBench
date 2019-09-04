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
struct genwqe_dev {int slu_unitcfg; } ;

/* Variables and functions */

__attribute__((used)) static inline int genwqe_get_slu_id(struct genwqe_dev *cd)
{
	return (int)((cd->slu_unitcfg >> 32) & 0xff);
}