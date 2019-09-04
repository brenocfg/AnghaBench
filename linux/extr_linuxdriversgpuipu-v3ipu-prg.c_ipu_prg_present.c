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
struct ipu_soc {scalar_t__ prg_priv; } ;

/* Variables and functions */

bool ipu_prg_present(struct ipu_soc *ipu)
{
	if (ipu->prg_priv)
		return true;

	return false;
}