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
struct camif_vp {int /*<<< orphan*/  offset; int /*<<< orphan*/  id; TYPE_1__* camif; } ;
struct TYPE_2__ {scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ S3C_CAMIF_REG_CISTATUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static inline u32 camif_hw_get_status(struct camif_vp *vp)
{
	return readl(vp->camif->io_base + S3C_CAMIF_REG_CISTATUS(vp->id,
								vp->offset));
}