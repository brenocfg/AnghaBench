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
struct ipu_vdi {int dummy; } ;
struct ipu_soc {struct ipu_vdi* vdi_priv; } ;

/* Variables and functions */

struct ipu_vdi *ipu_vdi_get(struct ipu_soc *ipu)
{
	return ipu->vdi_priv;
}