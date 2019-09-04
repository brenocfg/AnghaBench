#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int position; TYPE_2__* channel; } ;
struct tegra_ivc {int num_frames; TYPE_3__ tx; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct TYPE_5__ {TYPE_1__ tx; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void tegra_ivc_advance_tx(struct tegra_ivc *ivc)
{
	WRITE_ONCE(ivc->tx.channel->tx.count,
		   READ_ONCE(ivc->tx.channel->tx.count) + 1);

	if (ivc->tx.position == ivc->num_frames - 1)
		ivc->tx.position = 0;
	else
		ivc->tx.position++;
}