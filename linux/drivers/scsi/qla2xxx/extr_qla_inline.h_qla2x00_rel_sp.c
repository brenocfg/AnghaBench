#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  qpair; int /*<<< orphan*/  vha; } ;
typedef  TYPE_1__ srb_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA_VHA_MARK_NOT_BUSY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2xxx_rel_qpair_sp (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static inline void
qla2x00_rel_sp(srb_t *sp)
{
	QLA_VHA_MARK_NOT_BUSY(sp->vha);
	qla2xxx_rel_qpair_sp(sp->qpair, sp);
}