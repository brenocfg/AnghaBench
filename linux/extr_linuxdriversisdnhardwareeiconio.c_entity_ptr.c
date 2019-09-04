#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t byte ;
struct TYPE_7__ {scalar_t__ io; } ;
struct TYPE_6__ {TYPE_1__* e_tbl; } ;
struct TYPE_5__ {int /*<<< orphan*/ * e; } ;
typedef  TYPE_2__* PISDN_ADAPTER ;
typedef  int /*<<< orphan*/  ENTITY ;
typedef  TYPE_3__ ADAPTER ;

/* Variables and functions */

ENTITY *entity_ptr(ADAPTER *a, byte e_no)
{
	PISDN_ADAPTER IoAdapter;
	IoAdapter = (PISDN_ADAPTER)a->io;
	return (IoAdapter->e_tbl[e_no].e);
}