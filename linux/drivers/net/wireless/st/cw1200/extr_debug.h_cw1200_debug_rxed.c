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
struct cw1200_common {TYPE_1__* debug; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx; } ;

/* Variables and functions */

__attribute__((used)) static inline void cw1200_debug_rxed(struct cw1200_common *priv)
{
	++priv->debug->rx;
}