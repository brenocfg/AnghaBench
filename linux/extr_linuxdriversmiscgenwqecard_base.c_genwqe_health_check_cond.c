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
typedef  int u64 ;
struct genwqe_dev {int dummy; } ;

/* Variables and functions */
 int GFIR_ERR_TRIGGER ; 
 int /*<<< orphan*/  IO_SLC_CFGREG_GFIR ; 
 int __genwqe_readq (struct genwqe_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ genwqe_recovery_on_fatal_gfir_required (struct genwqe_dev*) ; 

__attribute__((used)) static int genwqe_health_check_cond(struct genwqe_dev *cd, u64 *gfir)
{
	*gfir = __genwqe_readq(cd, IO_SLC_CFGREG_GFIR);
	return (*gfir & GFIR_ERR_TRIGGER) &&
		genwqe_recovery_on_fatal_gfir_required(cd);
}