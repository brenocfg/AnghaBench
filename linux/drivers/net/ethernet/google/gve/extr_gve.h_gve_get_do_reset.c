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
struct gve_priv {int /*<<< orphan*/  service_task_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GVE_PRIV_FLAGS_DO_RESET ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool gve_get_do_reset(struct gve_priv *priv)
{
	return test_bit(GVE_PRIV_FLAGS_DO_RESET, &priv->service_task_flags);
}