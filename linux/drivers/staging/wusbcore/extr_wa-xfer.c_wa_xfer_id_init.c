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
struct wa_xfer {TYPE_1__* wa; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  xfer_id_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_return (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wa_xfer_id_init(struct wa_xfer *xfer)
{
	xfer->id = atomic_add_return(1, &xfer->wa->xfer_id_count);
}