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
struct TYPE_2__ {int /*<<< orphan*/  disconnected; int /*<<< orphan*/  connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  _scif_zap_mmaps (int,int /*<<< orphan*/ *) ; 
 TYPE_1__ scif_info ; 

void scif_zap_mmaps(int node)
{
	_scif_zap_mmaps(node, &scif_info.connected);
	_scif_zap_mmaps(node, &scif_info.disconnected);
}